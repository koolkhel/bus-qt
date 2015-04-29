#include "backend.h"
#include "gpsdpositionsource.h"
#include "gpsdsatellitesource.h"

//#define SERVER_ADDRESS "serv.indigosystem.ru"
#define SERVER_ADDRESS "192.168.91.1"

#define SERVER_PORT 9100
#define GPS_SEND_INTERVAL (5 * 1000)

Backend::Backend(QObject *parent)
: QObject(parent),
receive_state(NOTHING),
message_length(0),
  satellites_used(0)
{
    QFile key_file("/opt/key.txt");
    if (key_file.open(QIODevice::ReadOnly)) {
        // c8d1d4dc-f845-11e2-b1b2-000c29d2c11e
        QString key = QString::fromLocal8Bit(key_file.readLine().data()).replace("-", "").trimmed();
        qDebug() << key;

        bool ok = false;
        u_int64_t least = key.mid(0, 16).toULongLong(&ok, 16);
        u_int64_t most = key.mid(16, 16).toULongLong(&ok, 16);

        qDebug() << QString("%1 %2").arg(least, 0, 16).arg(most, 0, 16);

        if (ok) {
            deviceId.set_least_significant_bits(least);
            deviceId.set_most_significant_bits(most);
        }
    }

	socket = new QTcpSocket(this);
	socket->setSocketOption(QAbstractSocket::LowDelayOption, QVariant(1));
	connect(socket, SIGNAL(readyRead()), SLOT(readyRead()), Qt::QueuedConnection);
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(disconnected()));
	connect(socket, SIGNAL(connected()), SLOT(connected()));
	connect(socket, SIGNAL(connected()), SLOT(flushOrderEvents()));
	connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));

    //positionSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode, this);
    qDebug() << "QGeoPositionInfoSource";
    QStringList sources = QGeoPositionInfoSource::availableSources();
    foreach (QString source, sources) {
        qDebug() << "gps source: " << source;
    }

    qDebug() << "QGeoSatelliteInfoSource";
    QStringList satSources = QGeoSatelliteInfoSource::availableSources();
    foreach (QString source, satSources) {
        qDebug() << "satellite source: " << source;
    }

    QThread *nav_thread = new QThread(this);

    QGeoSatelliteInfoSource *satSource  = new GpsdSatelliteSource();
    if (satSource) {
        satSource->moveToThread(nav_thread);
        connect(satSource, SIGNAL(satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &)), SLOT(satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &)));       
        satSource->startUpdates();
    }

    positionSource = new GpsdPositionSource();
    //positionSource = QGeoPositionInfoSource::createDefaultSource(nav_thread);
    if (positionSource) {
        positionSource->moveToThread(nav_thread);
        connect(positionSource, SIGNAL(positionUpdated(const QGeoPositionInfo &)), SLOT(positionUpdated(const QGeoPositionInfo &)));

        positionSource->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        positionSource->setUpdateInterval(5000);
        positionSource->startUpdates();
    } else {
        qDebug() << "no GPS available!";
    }

	gpsTimer = new QTimer(this);
	gpsTimer->setSingleShot(false);
	gpsTimer->setInterval(GPS_SEND_INTERVAL);
	connect(gpsTimer, SIGNAL(timeout()), SLOT(sendLocationData()));
	gpsTimer->start();
		
    nav_thread->start();
}

Backend::~Backend()
{
}

// Static.
using namespace google::protobuf::io;
// i know it's bad
#ifndef UNDER_CE
int CodedInputStream::default_recursion_limit_ = 100;
#endif

// remove if any problems with big protobuf
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

void Backend::readyRead()
{
	int bytes_avail = socket->bytesAvailable();
	//qDebug() << "ready read" << bytes_avail << "bytes";

	QByteArray data = socket->read(bytes_avail);
	receiveBuffer.pushAll(data);
	consumeSocketData();
}

void Backend::connected()
{
	if (socket->state() == QAbstractSocket::ConnectedState) {
		qDebug() << "connected";
		emit connectedToServer(true);
	}
}

void Backend::disconnected()
{
	if (socket->state() != QAbstractSocket::ConnectedState) {
		qDebug() << "disconnected";
		emit connectedToServer(false);
		QTimer::singleShot(5000, this, SLOT(reconnect()));
	}
}

void Backend::error(QAbstractSocket::SocketError &error)
{
	qDebug() << "error" << socket->errorString();
}

void Backend::reconnect()
{
	socket->connectToHost(SERVER_ADDRESS, SERVER_PORT);
}

void Backend::stamp_uuid(indigo_msg &var)
{
    var.mutable_device_id()->CopyFrom(deviceId);
}

void Backend::sendEvent(indigo_event event)
{
    indigo_msg var;
    stamp_uuid(var);

	orderEventsQueue.push(var);
	flushOrderEvents();
}

void Backend::sendMessageQueued(indigo_msg var)
{
    stamp_uuid(var);

	orderEventsQueue.push(var);
	flushOrderEvents();
}

// "гарантия" доставки
void Backend::flushOrderEvents()
{		
	while (!orderEventsQueue.isEmpty()) {
		if (socket->state() == QTcpSocket::ConnectedState) {
            indigo_msg var = orderEventsQueue.peek();
			
			char buffer[1024];
			google::protobuf::io::ArrayOutputStream arr(buffer, sizeof(buffer));
			google::protobuf::io::CodedOutputStream output(&arr);

			output.WriteVarint32(var.ByteSize());
			var.SerializeToCodedStream(&output);

			socketMutex.lock();

			qint64 toWrite = output.ByteCount();
			qint64 result = socket->write(buffer, toWrite);
			//qDebug() << "send safe:" << output.ByteCount() << "bytes";
			socket->flush();
			socketMutex.unlock();
			if ((result != -1) && (result == toWrite)) {
				orderEventsQueue.pop();
			} else {
				socket->disconnect();
				break;
			}

		} else {
			break;
		}
	}
}


// сообщение не будет доставлено, если нет связи
void Backend::send_message(indigo_msg &var)
{
	char buffer[1024];
	google::protobuf::io::ArrayOutputStream arr(buffer, sizeof(buffer));
	google::protobuf::io::CodedOutputStream output(&arr);

    stamp_uuid(var);

	output.WriteVarint32(var.ByteSize());
	var.SerializeToCodedStream(&output);

	if (socket->state() == QTcpSocket::ConnectedState) {
		socketMutex.lock();
		if (socket->write(buffer, output.ByteCount()) == -1) {
			socket->disconnect();
		}
		//qDebug() << "send unsafe: " << output.ByteCount() << "bytes";
		socket->flush();
		socketMutex.unlock();
	}
}

#if 0
void Backend::protobuf_message_slot(const google::protobuf::uint8* begin, google::protobuf::uint32 length)
{
//	ui.serverMessage->setPlainText(QString::fromUtf8(var.text_string().c_str()));
	logger->addLine(QString::fromUtf8(var.text_string().c_str()));
}
#endif

#define PROBABLE_VARINT32_SIZE 2
void Backend::consumeSocketData()
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
				qDebug("ERROR =================================================");
				qDebug("ERROR =================================================");
				qDebug("ERROR =================================================");
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
            indigo_msg var;

			google::protobuf::io::ArrayInputStream arrayIn(message_start, message_length);
			google::protobuf::io::CodedInputStream codedIn(&arrayIn);	
			google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(message_length);
			if (var.ParseFromCodedStream(&codedIn)) {
				emit protobuf_message(var);
			}
			codedIn.PopLimit(msgLimit);

			// передаётся по значению
			
			receive_state = NOTHING;
			break;
		}
	}
}

void Backend::satellitesInUseUpdated(const QList<QGeoSatelliteInfo> & satellites)
{
    qDebug() << "satellites used:" << satellites.count();

    satellites_used = satellites.count();

    emit newSatellitesUsed(satellites.count());
}

void Backend::positionUpdated(const QGeoPositionInfo &update) 
{
	// надо будет фильтровать данные, чтобы скорость сохранялась. В разных сообщениях её может не быть, так что -- это проблема, что ли?
	if (update.isValid()) {
		qDebug() << "longitude" << update.coordinate().longitude() << "latitude" << update.coordinate().latitude();

        positionMessage.clear_coordinates();
        indigo_geo *geo = positionMessage.add_coordinates();

        geo->set_longitude(update.coordinate().longitude());
        geo->set_latitude(update.coordinate().latitude());
        geo->set_unixtime(QDateTime::currentMSecsSinceEpoch() / 1000);
        geo->set_satellites_used(satellites_used);
		
		if (update.hasAttribute(QGeoPositionInfo::GroundSpeed)) {
			int speed = (int) (update.attribute(QGeoPositionInfo::GroundSpeed) * 3.6);

            geo->set_speed_kmh(speed);
			emit newSpeed(speed);
            qDebug() << "speed: " << speed;

            detectStartStop(speed);
		}

		emit newPosition(update.coordinate());
	}
}

void Backend::sendLocationData()
{
	// нет связи -- не доставлено    
	send_message(positionMessage);	
}

void Backend::detectStartStop(int speed)
{
	if (speed >= 20) {
		emit movementStart(1);
	} else if (speed == 0) {
		emit movementStart(0);		
	}
}
