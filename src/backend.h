#ifndef BACKEND_H
#define BACKEND_H

#include <QtCore>
#include <QtNetwork/QTcpSocket>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

#include <google/protobuf/text_format.h>

#include "indigo.pb.h"
#include "indigoqueue.h"

#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QGeoSatelliteInfoSource>

//#include "qnmeapositioninfosource.h"

#include <QObject>

class Backend : public QObject
{
	Q_OBJECT

public:
	Backend(QObject *parent);
    ~Backend();
    indigo_UUID getDeviceId() { return deviceId; }

signals:
	// передаётся по значению
    void protobuf_message(indigo_msg message);
	void connectedToServer(bool status);
    void deviceIdChanged(int deviceId);
	void newPosition(QGeoCoordinate coordinate);
	void newSpeed(int speed_kmh);
	void newSatellitesUsed(int satellitesUsed);
	// 0 == stop, 1 == start
	void movementStart(int start);
	
public slots:
	// from gps
	void positionUpdated(const QGeoPositionInfo &update);
    void satellitesInUseUpdated(const QList<QGeoSatelliteInfo> & satelliteInfo);

    void sendMessageQueued(indigo_msg var);
    void sendEvent(indigo_event event);
    //void sendOrderEvent(indigo_event event, ITaxiOrder *order);

	// from timer
	void sendLocationData();
	
	void readyRead();
	void connected();
	void error(QAbstractSocket::SocketError &error);
	void disconnected();
	void reconnect();
	void flushOrderEvents();

	
    void send_message(indigo_msg &var);

private:
    void stamp_uuid(indigo_msg &var);
	QSettings *settingsIniFile;
	void consumeSocketData();

	IndigoOrderQueue orderEventsQueue;

	QTcpSocket *socket;
	QMutex socketMutex;
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

    indigo_UUID deviceId;

	QTimer *gpsTimer;
    QGeoPositionInfoSource *positionSource;
    indigo_msg positionMessage;

    int satellites_used;
	
	void detectStartStop(int speed);
};

#endif // BACKEND_H
