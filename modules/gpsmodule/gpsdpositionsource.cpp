/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtCore>

#include "gpsdpositionsource.h"
#include <errno.h>

GpsdPositionSource::GpsdPositionSource(QObject *parent)
    : QGeoPositionInfoSource(parent),
      logFile(new QFile(this)),
      timer(NULL),
      connected(false)
{
    qRegisterMetaType<QGeoPositionInfo>("QGeoPositionInfo");
    connectGpsd();
}

GpsdPositionSource::~GpsdPositionSource()
{
    if (connected) {
        connected = false;
        gps_close(&gps_data);
    }
}

void GpsdPositionSource::connectGpsd()
{
    int result = gps_open("127.0.0.1", DEFAULT_GPSD_PORT, &gps_data);
    if (result) {
        QTimer::singleShot(1000 /* ms */, SLOT(connectGpsd()));
    } else {
        connected = true;
    }
}

void GpsdPositionSource::poll()
{
    requestUpdate(updateInterval());
}

QGeoPositionInfo GpsdPositionSource::lastKnownPosition(bool /*fromSatellitePositioningMethodsOnly*/) const
{
    return lastPosition;
}

GpsdPositionSource::PositioningMethods GpsdPositionSource::supportedPositioningMethods() const
{
    return AllPositioningMethods;
}

int GpsdPositionSource::minimumUpdateInterval() const
{
    return 500;
}

void GpsdPositionSource::startUpdates()
{
    gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

    int interval = updateInterval();
    if (interval < minimumUpdateInterval())
        interval = minimumUpdateInterval();

    if (timer == NULL) {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(poll()));
    }
    timer->start(interval);
}

void GpsdPositionSource::stopUpdates()
{
    gps_stream(&gps_data, WATCH_DISABLE, NULL);

    timer->stop();
}

void GpsdPositionSource::requestUpdate(int timeout /* ms */)
{
    if (!connected) {
        qDebug() << "gpsd not connected";
        return;
    }

    // 0.5 s
    if (!gps_waiting(&gps_data, timeout * 1000 / 2)) {

        emit updateTimeout();
    }

    if (gps_read(&gps_data) == -1) {
        // error in errno
        qDebug() << "gps_read: " << errno;
    } else {

        if (gps_data.fix.mode >= MODE_2D) {
            // отдать координату
            QGeoCoordinate coordinate(gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.altitude);

            QGeoPositionInfo update(coordinate, QDateTime::fromTime_t(gps_data.fix.time));

            update.setAttribute(QGeoPositionInfo::GroundSpeed, gps_data.fix.speed);
            update.setAttribute(QGeoPositionInfo::Direction, gps_data.fix.track);
            update.setAttribute(QGeoPositionInfo::VerticalSpeed, gps_data.fix.climb);
            update.setAttribute(QGeoPositionInfo::HorizontalAccuracy, gps_data.fix.epx + gps_data.fix.epy);

            lastPosition = update;
            if (update.isValid()) {
                emit positionUpdated(update);
            }
        }
    }
}

QGeoPositionInfoSource::Error GpsdPositionSource::error() const
{
    return QGeoPositionInfoSource::NoError;
}
