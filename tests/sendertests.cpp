#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>


#include <QtSql>

#include "sender_message.pb.h"
#include "geo_message.pb.h"
#include "blackbox_message.pb.h"

TEST(SENDER, DISABLED_load) {
    QStringList c;
    c << "[modules]"
      << "sender_instance=sender"
      << "[sender_instance]"
      << "serverAddress=serv.indigosystem.ru"
      << "serverPort=9909"
      << "uuid=c8d1d4dc-f845-11e2-b1b2-000c29d2c11e";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    Module *module = dispatcher->getModuleInstances().value("sender_instance");
    ASSERT_TRUE(module != NULL);

    module->stop();
}

TEST(SENDER, connect) {
    QStringList c;
    c << "[modules]"
      << "sender_instance=sender"
       << "zlogs_instance=logs"
       << "test_instance=test_module"
       << "[zlogs_instance]"
       << "console=true"
       << "module=false"
        << "sender=true"
       << "zmq=false"
      << "[sender_instance]"
      << "serverAddress=127.0.0.1"
      << "serverPort=9909"
      << "uuid=c8d1d4dc-f845-11e2-b1b2-000c29d2c11e";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    Module *module = dispatcher->getModuleInstances().value("sender_instance");
    ASSERT_TRUE(module != NULL);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    ASSERT_TRUE(testModule != NULL);

    for (int i = 0; i < 200; i++) {
        ::indigo::pb::internal_msg positionMessage;
        ::indigo::pb::indigo_geo *geo = positionMessage.MutableExtension(::indigo::pb::indigo_geo::geo_coords_in);

        positionMessage.set_id(i);

        geo->set_longitude(35.5);
        geo->set_latitude(36.6);
        geo->set_unixtime(QDateTime::currentMSecsSinceEpoch() / 1000);
        geo->set_satellites_used(10);

        testModule->sendMessage(positionMessage, "tosend");
        qApp->processEvents();
    }

    usleep(1000 * 1000);

    for (int i = 0; i < 20000; i++) {
        qApp->processEvents();
        usleep(1000);
    }

    module->stop();
}
