#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

#include "module.h"

#include <QGeoPositionInfo>
#include <QGeoSatelliteInfo>

Q_DECLARE_LOGGING_CATEGORY(GPSMODULEC)

class GPSMODULE : public Module
{
	Q_OBJECT

public:
    GPSMODULE(QObject *parent = 0);
    virtual ~GPSMODULE();
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);

private slots:
    void positionUpdated(const QGeoPositionInfo &);
    void satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &);

private:
    int last_satellite_count;
};

#endif // SKEL_H
