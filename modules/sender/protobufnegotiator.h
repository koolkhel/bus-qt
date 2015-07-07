#ifndef PROTOBUFNEGOTIATOR_H
#define PROTOBUFNEGOTIATOR_H

#include <QObject>
#include <QAbstractSocket>

#include "sender_message.pb.h"

#include <indigoqueue.h>

class QTcpSocket;

class ProtobufNegotiator : public QObject
{
    Q_OBJECT
public:
    explicit ProtobufNegotiator(QString serverAddress, int serverPort, ::indigo::pb::indigo_UUID uuid, QObject *parent);
    virtual ~ProtobufNegotiator() {}
    void start();
    void stop();

signals:
    void messageReceived(::indigo::pb::indigo_msg &message);
    void connectedToServer(bool connected);

public slots:
    void queueMessage(int id, ::indigo::pb::indigo_msg &message);

private slots:
    void readyRead();
    void connected();
    void error(QAbstractSocket::SocketError &error);
    void disconnected();
    void reconnect();
    void flushOrderEvents();

private:
    void stamp_uuid(::indigo::pb::indigo_msg &var);
    void consumeSocketData();

    IndigoQueue receiveBuffer;

    enum receive_state_t
    {
        NOTHING = 0,
        MESSAGE_RECEIVING, // -> NOTHING
    };

    receive_state_t receive_state;
    int index;
    google::protobuf::uint8 message_buffer[2048];
    google::protobuf::uint32 message_length;
    const google::protobuf::uint8 *message_start;
    int remainder;

    QString _serverAddress;
    int _serverPort;
    ::indigo::pb::indigo_UUID _deviceId;

    QTcpSocket *socket;
};

#endif // PROTOBUFNEGOTIATOR_H
