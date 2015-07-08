#include "protobufnegotiator.h"

#include <QTcpSocket>
#include <QTimer>
#include <QDebug>

#include "sender.h"

#include "sender_message.pb.h"
#include "google/protobuf/io/zero_copy_stream_impl_lite.h"
#include "google/protobuf/io/coded_stream.h"

namespace google {
    namespace protobuf {
        namespace internal {
            const string kEmptyString;
        }
    }
}

inline const google::protobuf::uint8* ReadVarint32FromArray(const google::protobuf::uint8* buffer, google::protobuf::uint32* value) {
    static const int kMaxVarintBytes = 10;
    static const int kMaxVarint32Bytes = 5;

    // Fast path:  We have enough bytes left in the buffer to guarantee that
    // this read won't cross the end, so we can skip the checks.
    const google::protobuf::uint8* ptr = buffer;
    google::protobuf::uint32 b;
    google::protobuf::uint32 result;

    b = *(ptr++); result  = (b & 0x7F)      ; if (!(b & 0x80)) goto done;
    b = *(ptr++); result |= (b & 0x7F) <<  7; if (!(b & 0x80)) goto done;
    b = *(ptr++); result |= (b & 0x7F) << 14; if (!(b & 0x80)) goto done;
    b = *(ptr++); result |= (b & 0x7F) << 21; if (!(b & 0x80)) goto done;
    b = *(ptr++); result |=  b         << 28; if (!(b & 0x80)) goto done;

    // If the input is larger than 32 bits, we still need to read it all
    // and discard the high-order bits.
    for (int i = 0; i < kMaxVarintBytes - kMaxVarint32Bytes; i++) {
        b = *(ptr++); if (!(b & 0x80)) goto done;
    }

    // We have overrun the maximum size of a varint (10 bytes).  Assume
    // the data is corrupt.
    return NULL;

done:
    *value = result;
    return ptr;
}


ProtobufNegotiator::ProtobufNegotiator(QString serverAddress, int serverPort, ::indigo::pb::indigo_UUID uuid, QObject *parent = 0)
    :
    _serverAddress(serverAddress),
    _serverPort(serverPort),
    _deviceId(uuid),
    QObject(parent)
{

}

void ProtobufNegotiator::start()
{
    socket = new QTcpSocket(this);
    socket->setSocketOption(QAbstractSocket::LowDelayOption, QVariant(1));

    connect(socket, SIGNAL(readyRead()), SLOT(readyRead()), Qt::QueuedConnection);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(disconnected()));
    connect(socket, SIGNAL(connected()), SLOT(connected()));
    //connect(socket, SIGNAL(connected()), SLOT(flushOrderEvents()));
    connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));

    reconnect();
}

void ProtobufNegotiator::stop()
{
    socket->close();
    socket->deleteLater();
}

void ProtobufNegotiator::readyRead()
{
    int bytes_avail = socket->bytesAvailable();
    qCDebug(SENDERC) << "ready read" << bytes_avail << "bytes";

    QByteArray data = socket->read(bytes_avail);
    receiveBuffer.pushAll(data);
    consumeSocketData();
}

void ProtobufNegotiator::connected()
{
    qCDebug(SENDERC) << "socket state " << socket->state();
    if (socket->state() == QAbstractSocket::ConnectedState) {
        qCDebug(SENDERC) << "connected";
        emit connectedToServer(true);
    }
}

void ProtobufNegotiator::disconnected()
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        qCDebug(SENDERC) << "disconnected";
        emit connectedToServer(false);
        QTimer::singleShot(5000, this, SLOT(reconnect()));
    }
}

void ProtobufNegotiator::error(QAbstractSocket::SocketError &error)
{
    qCDebug(SENDERC) << "error" << socket->errorString();
}

void ProtobufNegotiator::reconnect()
{
    qCDebug(SENDERC) << QString("connecting to %1 port %2").arg(_serverAddress).arg(_serverPort);
    socket->connectToHost(_serverAddress, _serverPort);
}

void ProtobufNegotiator::stamp_uuid(::indigo::pb::indigo_msg &var)
{
    var.mutable_device_id()->CopyFrom(_deviceId);
}

// сообщение не будет доставлено, если нет связи
void ProtobufNegotiator::queueMessage(::indigo::pb::indigo_msg &var)
{
    char buffer[8192];
    google::protobuf::io::ArrayOutputStream arr(buffer, sizeof(buffer));
    google::protobuf::io::CodedOutputStream output(&arr);

    stamp_uuid(var);

    output.WriteVarint32(var.ByteSize());
    var.SerializeToCodedStream(&output);

    if (socket->state() == QTcpSocket::ConnectedState) {
        if (socket->write(buffer, output.ByteCount()) == -1) {
            socket->disconnect();
        }
        socket->flush();
        qCDebug(SENDERC) << "seems to send ok";
    } else {
        qCWarning(SENDERC) << "socket not connected, exiting";
    }
}

#define PROBABLE_VARINT32_SIZE 2
void ProtobufNegotiator::consumeSocketData()
{

    int varint32_byte_count = 0;


    forever {
        switch (receive_state) {
        case NOTHING:
            if (receiveBuffer.size() < PROBABLE_VARINT32_SIZE)
                return;

            index = 0;
            message_length = 0;
            memset(message_buffer, 0, sizeof(message_buffer));
            // pop succeeds every time
            for (int i = 0; i < PROBABLE_VARINT32_SIZE; i++) {
                message_buffer[index++] = receiveBuffer.pop();
            }

            message_start = ReadVarint32FromArray(message_buffer, &message_length);
            varint32_byte_count = message_start - &message_buffer[0];
            remainder = message_length - (PROBABLE_VARINT32_SIZE - varint32_byte_count);
            if (remainder > 10000 || remainder < 0) {
                qCDebug(SENDERC, "ERROR =================================================");
                qCDebug(SENDERC, "ERROR =================================================");
                qCDebug(SENDERC, "ERROR =================================================");
                socket->disconnectFromHost();
            }
            receive_state = MESSAGE_RECEIVING;

            break;
        case MESSAGE_RECEIVING:
            int count = receiveBuffer.size();
            while (remainder > 0) {
                if (count == 0)
                    return;
                message_buffer[index++] = receiveBuffer.pop();
                remainder--;
                count--;
            }

            // next part is coming
            if (remainder != 0) {
                break;
            }
            ::indigo::pb::indigo_msg var;

            google::protobuf::io::ArrayInputStream arrayIn(message_start, message_length);
            google::protobuf::io::CodedInputStream codedIn(&arrayIn);
            google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(message_length);

            if (var.ParseFromCodedStream(&codedIn)) {
                emit messageReceived(var);
            }
            codedIn.PopLimit(msgLimit);

            // передаётся по значению

            receive_state = NOTHING;
            break;
        }
    }
}
