#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/gpsmodule/gpsmodule.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>


#include "geo_message.pb.h"

void reset(::indigo::pb::indigo_geo *geo) {
    geo->set_longitude(123);
    geo->set_latitude(321);
    geo->mutable_unixtime()->set_time(QDateTime::currentMSecsSinceEpoch() / 1000);
    geo->set_satellites_used(0);
    geo->set_speed_kmh(0);
}

TEST(STOPS, fake_gps_pos) {
    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;

    c << "[modules]"
      << "stops_instance=stops"
      << "test_instance=test_module"
      << "[stops_instance]"
      << "inputTopics=raw_gps"
      << "typeOfLogic=1";

    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));


    dispatcher->startAll();

    testModule->subscribeTopic("stoped");

    QSignalSpy spy(testModule, SIGNAL(messageReceivedSignal()));

    ::indigo::pb::internal_msg positionMessage;
    ::indigo::pb::indigo_geo *geo = positionMessage.MutableExtension(::indigo::pb::indigo_geo::geo_coords_in);


    for(int i = 0; i < 5; ++i) {
        reset(geo);
        for(int j = 0; j < 10; ++j) {
            testModule->sendMessage(positionMessage, "raw_gps");
        }
        spy.wait(1000);

        geo->set_speed_kmh(100*1000);

        testModule->sendMessage(positionMessage, "raw_gps");
    }

    qDebug() << spy.count();
}

TEST(STOPS, fake_gps_speed) {
    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;

    c << "[modules]"
      << "stops_instance=stops"
      << "test_instance=test_module"
      << "[stops_instance]"
      << "inputTopics=raw_gps"
      << "typeOfLogic=0";
    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));


    dispatcher->startAll();

    testModule->subscribeTopic("stoped");

    QSignalSpy spy(testModule, SIGNAL(messageReceivedSignal()));

    ::indigo::pb::internal_msg positionMessage;
    ::indigo::pb::indigo_geo *geo = positionMessage.MutableExtension(::indigo::pb::indigo_geo::geo_coords_in);


    for(int i = 0; i < 5; ++i) {
        reset(geo);
        testModule->sendMessage(positionMessage, "raw_gps");

        spy.wait(1000);

        geo->set_longitude(100*1000);

        testModule->sendMessage(positionMessage, "raw_gps");
    }
    qDebug() << spy.count();
}

TEST(STOPS, real_gps) {
    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;

    c << "[modules]"
      << "gps_instance=gpsmodule"
      << "test_instance=test_module"
      << "stops_instance=stops"
      << "[stops_instance]"
      << "inputTopics=raw_gps";
    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));


    dispatcher->startAll();

    testModule->subscribeTopic("stops");

    QSignalSpy spy(testModule, SIGNAL(messageReceivedSignal()));

    spy.wait();
}
