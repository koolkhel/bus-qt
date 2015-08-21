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
#include "ui_message.pb.h"

TEST(UI, init) {
    QStringList c;
    c << "[modules]"
      << "ui_instance=UI"
      << "test_instance=test_module"
      << "[ui_instance]"
      << "inputTopic=server_respond";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    qApp->processEvents();
    usleep(1000 * 1000);
    qApp->processEvents();
    usleep(1000 * 1000);
    qApp->processEvents();

    Module *module = dispatcher->getModuleInstances().value("ui_instance");
    ASSERT_TRUE(module != NULL);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    ::indigo::pb::internal_msg msg;
    ::indigo::pb::route_info *route_info = msg.MutableExtension(::indigo::pb::route_info::route_info_in);
    route_info->set_bus_number("H200EM");
    route_info->set_route_name("2");

    ::indigo::pb::schedule_station *station = route_info->add_station();
    station->set_station_name("Конечная  Левая");
    for(int i = 1; i < 11; ++i) {
        station = route_info->add_station();
        station->set_station_name(QString("Промежуточная %1").arg(i).toStdString());
    }
    station = route_info->add_station();
    station->set_station_name("Конечная Правая");
    for(int i = 0; i < 12; ++i) {
        ::indigo::pb::station_visit_schedule_time *visit_time = route_info->mutable_station(i)->add_schedule_times();
        visit_time->set_visit_time(rand() % 6 + 1 * 60);
        visit_time->set_daytime_start(0);
        visit_time->set_daytime_end(60 * 60 * 24);
    }

     QSignalSpy spy(testModule, SIGNAL(messageReceivedSignal()));
     for (int j = 0; j < 4; j++) {
         usleep(1000 * 1000);
         for (int i = 0; i < 20000; i++) {
             qApp->processEvents();
        }
     }
     spy.wait(1000);
     spy.wait(1000);

    testModule->sendMessage(msg, "server_respond");
    for (int j = 0; j < 4; j++) {
        usleep(1000 * 1000);
        for (int i = 0; i < 20000; i++) {
            qApp->processEvents();
       }
    }
    spy.wait(1000);
    spy.wait(1000);
    ::indigo::pb::internal_msg movement;

    ::indigo::pb::schedule_movement_update *move_info =
                        movement.MutableExtension(
                            ::indigo::pb::schedule_movement_update::schedule_update_in);

    move_info->mutable_this_bus()->set_previous_station_visit_time(70);
    QVector <indigo::pb::bus_on_route *> buses;
    indigo::pb::bus_on_route * bus;
    for(int i = 0; i < 5; ++i) {
        bus = move_info->add_buses();
        buses.push_back(bus);
        bus->set_busname(QString("EHB-2%1").arg(i+1).toStdString()) ;
        bus->set_seconds_from_route_start(60*(rand() % 7 + 1));
        bus->set_route_order(i+2);
        bus->set_time_to_prev(i + 60 + rand() % 80);
        bus->set_time_to_next(i + 60 + rand() % 80);
        bus->set_distance_to_next_m(1000);
        bus->set_distance_to_prev_m(1000);
        bus->set_position(1.2 + (rand() % 10)/10.0 + i);
    }

    bus = move_info->add_buses();
    buses.push_back(bus);
    bus->set_busname(QString("H200EM").toStdString()) ;
    bus->set_seconds_from_route_start(60*(rand() % 7 + 1));
    bus->set_route_order(1);
    bus->set_time_to_prev( 60 + rand() % 80);
    bus->set_time_to_next(60 + rand() % 80);
    bus->set_distance_to_next_m(1000);
    bus->set_distance_to_prev_m(1000);
    bus->set_position(0);

    testModule->sendMessage(movement, "server_respond");
    spy.wait(4000);
    for (int j = 0; j < 10; j++) {
        usleep(1000 * 1000);

        for (int i = 0; i < 20000; i++) {
            qApp->processEvents();
            usleep(1000);
        }
    }

}
