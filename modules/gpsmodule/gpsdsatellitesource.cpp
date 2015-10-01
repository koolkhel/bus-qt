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

#include "gpsdsatellitesource.h"
#include <errno.h>

#include "gpsmodule.h"

GpsdSatelliteSource::GpsdSatelliteSource(QObject *parent)
    : QGeoSatelliteInfoSource(parent),
      timer(NULL),
      outputTimer(NULL),
      connected(false)
{
    qRegisterMetaType<QList<QGeoSatelliteInfo> >("QList<QGeoSatelliteInfo>");
    connectGpsd();
}

GpsdSatelliteSource::~GpsdSatelliteSource()
{
    if (connected) {
        connected = false;
        gps_close(&gps_data);
    }
}

void GpsdSatelliteSource::connectGpsd()
{
    int result = gps_open("127.0.0.1", DEFAULT_GPSD_PORT, &gps_data);
    if (result) {
        QTimer::singleShot(1000 /* ms */, SLOT(connectGpsd()));
    } else {
        connected = true;
    }
}

void GpsdSatelliteSource::poll()
{
    requestUpdate(updateInterval());
}

int GpsdSatelliteSource::minimumUpdateInterval() const
{
    return 100;
}

void GpsdSatelliteSource::startUpdates()
{
    qCDebug(GPSMODULEC) << "startUpdates";
    gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

    int interval = updateInterval();
    if (interval < minimumUpdateInterval())
        interval = minimumUpdateInterval();

    if (timer == NULL) {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(poll()));
    }
    timer->start(interval);

    if (outputTimer == NULL) {
        outputTimer = new QTimer(this);
        connect(outputTimer, SIGNAL(timeout()), SLOT(doOutput()));
        outputTimer->setInterval(5000);
        outputTimer->setSingleShot(false);
    }

    outputTimer->start();;
}

void GpsdSatelliteSource::stopUpdates()
{
    gps_stream(&gps_data, WATCH_DISABLE, NULL);

    timer->stop();
}

void GpsdSatelliteSource::requestUpdate(int timeout /* ms */)
{
    if (!connected) {
        qDebug() << "gpsd not connected";
        return;
    }

    // 500 microseconds
    if (!gps_waiting(&gps_data, 500)) {

        emit requestTimeout();
        return;
    }

    int result = gps_read(&gps_data);
    if (result == -1) {
        // error in errno
        qCDebug(GPSMODULEC) << "gps_read: " << errno;
    } else if (result > 0) {

        if (gps_data.fix.mode >= MODE_2D) {
            // отдать координату
            QList<QGeoSatelliteInfo> inView;
            QList<QGeoSatelliteInfo> inUse;

            QGeoSatelliteInfo satInfo;
            satInfo.setSatelliteSystem(QGeoSatelliteInfo::GLONASS);
            /* must build bit vector of which statellites are used from list */
            for (int i = 0; i < MAXCHANNELS; i++) {

                for (int j = 0; j < qMin(gps_data.satellites_used, MAXCHANNELS); j++) {
                    satInfo.setSatelliteIdentifier(gps_data.PRN[j]);
                    satInfo.setSignalStrength(gps_data.ss[j]);

                    if (gps_data.used[j] == gps_data.PRN[i]) {
                        inUse.append(satInfo);
                    }
                }                
            }

            for (int i = 0; i < qMin(gps_data.satellites_visible, MAXCHANNELS); i++) {
                satInfo.setSatelliteIdentifier(gps_data.PRN[i]);
                satInfo.setSignalStrength(gps_data.ss[i]);

                inView.append(satInfo);
            }

            _inView = inView;
            _inUse = inUse;
        }
    }
}

void GpsdSatelliteSource::doOutput()
{
    qCDebug(GPSMODULEC) << "doing SATELLITE output";
    if (_inView.size() > 0)
        emit satellitesInViewUpdated(_inView);
    if (_inUse.size() > 0)
        emit satellitesInUseUpdated(_inUse);
}

QGeoSatelliteInfoSource::Error GpsdSatelliteSource::error() const
{
    return QGeoSatelliteInfoSource::NoError;
}
