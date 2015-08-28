#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include "modules/vpnremote/vpnremote.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>

TEST(vpnRemote, load) {
    QStringList c;
    c << "[modules]"
      << "vpnremote_instance=vpnremote"
      << "test_instance=test_module"
      << "[vpnremote_instance]";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    for(int i = 0; i < 1000; ++i) {
        qApp->processEvents();
    }
    ::indigo::pb::internal_msg message;
    testModule->sendMessage(message, QString("startVPN"));

    for(int i = 0; i < 1000; ++i) {
        qApp->processEvents();
    }
}

TEST(vpnRemote, wrongStart) {
    QStringList c;
    c << "[modules]"
      << "vpnremote_instance=vpnremote"
      << "test_instance=test_module"
      << "[vpnremote_instance]"
      << "serverAddress=serv.indigosystem.ru"
      << "serverPort=9909"
      << "uuid=c8d1d4dc-f845-11e2-b1b2-000c29d2c11e";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));
    QSignalSpy spy(testModule, SIGNAL(messageReceivedSignal()));
    testModule->subscribeTopic("VPNInfo");

    ::indigo::pb::internal_msg message;
    testModule->sendMessage(message, QString("startVPN"));
    for(int i = 0; i < 1000*1000; ++i) {
        qApp->processEvents();
    }
    testModule->sendMessage(message, QString("getVPNInfo"));

    for(int i = 0; i < 1000*1000; ++i) {
        qApp->processEvents();
    }
    spy.wait(5000);

}
