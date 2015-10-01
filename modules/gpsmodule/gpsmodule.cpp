#include "gpsmodule.h"

#include "gpsdpositionsource.h"
#include "gpsdsatellitesource.h"

#include "geo_message.pb.h"

Q_LOGGING_CATEGORY(GPSMODULEC, "gpsmodule")

GPSMODULE::GPSMODULE(QObject *parent)
    : last_satellite_count(0)
{
    setParent(parent);

    this->name = "gpsmodule works";

    qCDebug(GPSMODULEC, "hello,world");
}

GPSMODULE::~GPSMODULE()
{

}

QStringList GPSMODULE::getPubTopics()
{
    QStringList topics;

    return topics;
}

void GPSMODULE::respond(QString topic, indigo::pb::internal_msg &message)
{
}

void GPSMODULE::start()
{
    //positionSource = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode, this);
    qCDebug(GPSMODULEC) << "QGeoPositionInfoSource";
    QStringList sources = QGeoPositionInfoSource::availableSources();
    foreach (QString source, sources) {
        qCDebug(GPSMODULEC) << "gps source: " << source;
    }

    qCDebug(GPSMODULEC) << "QGeoSatelliteInfoSource";
    QStringList satSources = QGeoSatelliteInfoSource::availableSources();
    foreach (QString source, satSources) {
        qCDebug(GPSMODULEC) << "satellite source: " << source;
    }

    QThread *nav_thread = new QThread(this);
    nav_thread->start();

    QGeoSatelliteInfoSource *satSource  = new GpsdSatelliteSource();
    if (satSource) {
        satSource->moveToThread(nav_thread);
        connect(satSource, SIGNAL(satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &)), SLOT(satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &)));
        satSource->setUpdateInterval(getConfigurationParameter("satUpdateInterval", QVariant(100)).toInt());
        QMetaObject::invokeMethod(satSource, "startUpdates", Qt::QueuedConnection);
        //satSource->startUpdates();
    }

    GpsdPositionSource *positionSource = new GpsdPositionSource();
    if (positionSource) {
        positionSource->moveToThread(nav_thread);
        connect(positionSource, SIGNAL(positionUpdated(const QGeoPositionInfo &)), SLOT(positionUpdated(const QGeoPositionInfo &)));

        positionSource->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        positionSource->setUpdateInterval(getConfigurationParameter("updateInterval", QVariant(100)).toInt());
        QMetaObject::invokeMethod(positionSource, "startUpdates", Qt::QueuedConnection);
        //positionSource->startUpdates();
    } else {
        qCDebug(GPSMODULEC) << "no GPS available!";
    }
}

void GPSMODULE::stop()
{
}

void GPSMODULE::positionUpdated(const QGeoPositionInfo &update)
{
    // надо будет фильтровать данные, чтобы скорость сохранялась. В разных сообщениях её может не быть, так что -- это проблема, что ли?
    if (!update.isValid())
        return;

    qCDebug(GPSMODULEC) << "longitude" << update.coordinate().longitude() << "latitude" << update.coordinate().latitude();


    ::indigo::pb::internal_msg positionMessage;
    ::indigo::pb::indigo_geo *geo = positionMessage.MutableExtension(::indigo::pb::indigo_geo::geo_coords_in);

    geo->set_longitude(update.coordinate().longitude());
    geo->set_latitude(update.coordinate().latitude());
    geo->mutable_unixtime()->set_time(QDateTime::currentMSecsSinceEpoch() / 1000);
    geo->set_satellites_used(last_satellite_count);

    if (update.hasAttribute(QGeoPositionInfo::GroundSpeed)) {
        int speed = (int) (update.attribute(QGeoPositionInfo::GroundSpeed) * 3.6);

        geo->set_speed_kmh(speed);
        qCDebug(GPSMODULEC) << "speed: " << speed;
    }

    publish(positionMessage, "raw_gps");
}

void GPSMODULE::satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &satellites)
{
    last_satellite_count = satellites.count();
}
