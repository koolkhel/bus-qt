#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "gpsmodule.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>

TEST(GPS, loading) {
    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;

    c << "[modules]" << "gps_instance=gpsmodule";
    dispatcher->initializeAll(c);
}
