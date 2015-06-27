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

    c << "[modules]" << "gps_instance=gpsmodule" << "test_instance=test_module";
    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));


    dispatcher->startAll();

    testModule->subscribeTopic("raw_gps");



    for (int i = 0; i < 5000; i++) {
        QSignalSpy spy(testModule, SIGNAL(messageReceivedSignal()));
        spy.wait(20);
        qApp->processEvents();
    }
}
