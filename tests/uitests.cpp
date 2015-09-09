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

TEST(UI, bigBaby) {
    QStringList c;
    c << "[modules]"
      << "ui_instance=UI"
      << "test_instance=test_module"
      << "[ui_instance]"
      << "inputTopic=server_respond";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();
    for(int i = 0; i < 5; ++i) {
        usleep(1000 * 1000);
        for(int i = 0; i < 10; ++i) {
            qApp->processEvents();
        }
    }

    QThread::currentThread()->setObjectName("system thread");
    dispatcher->dumpObjectInfo();
    dispatcher->dumpObjectTree();

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    ::indigo::pb::internal_msg msg;
    ::indigo::pb::route_info *route_info = msg.MutableExtension(::indigo::pb::route_info::route_info_in);
    route_info->set_bus_number("H200EM");
    route_info->set_route_name("2");

    ::indigo::pb::schedule_station *station = route_info->add_station();
    station->set_station_name("Конечная Левая");
    for(int i = 0; i < 10; ++i) {
        station = route_info->add_station();
        station->set_station_name(QString("Промежуточная %1").arg(i).toStdString());
    }
    station = route_info->add_station();
    station->set_station_name("Конечная Правая");
    for(int i = 0; i < route_info->station_size(); ++i) {
        ::indigo::pb::station_visit_schedule_time *visit_time = route_info->mutable_station(i)->add_schedule_times();
        visit_time->set_visit_time(rand() % 6 + 1 * 60);
        visit_time->set_daytime_start(0);
        visit_time->set_daytime_end(60 * 60 * 24);
    }
    testModule->sendMessage(msg, "server_respond");

    ::indigo::pb::internal_msg movement;

    ::indigo::pb::schedule_movement_update *move_info =
                        movement.MutableExtension(
                            ::indigo::pb::schedule_movement_update::schedule_update_in);

    move_info->mutable_this_bus()->set_previous_station_visit_time(70);
    QVector <indigo::pb::bus_on_route *> buses;
    indigo::pb::bus_on_route * bus;
    for(int i = 2; i < route_info->station_size(); ++i) {
        bus = move_info->add_buses();
        buses.push_back(bus);
        bus->set_busname(QString("EHB-2%1").arg(i+1).toStdString()) ;
        bus->set_seconds_from_route_start(60*(rand() % 7 + 1));
        bus->set_route_order(i);
        bus->set_time_to_prev(i + 60 + rand() % 80);
        bus->set_time_to_next(i + 60 + rand() % 80);
        bus->set_distance_to_next_m(1000);
        bus->set_distance_to_prev_m(1000);
        bus->set_position(0.5 +  i - 2 );
    }

    bus = move_info->add_buses();
    buses.push_back(bus);
    bus->set_busname(QString("H200EM").toStdString()) ;
    bus->set_seconds_from_route_start(60*(rand() % 7 + 1));
    bus->set_route_order(1);
    bus->set_time_to_prev( (60 + rand() % 80) * 1000);
    bus->set_time_to_next( (60 + rand() % 80) * 1000);
    bus->set_distance_to_next_m(1000);
    bus->set_distance_to_prev_m(1000);
    bus->set_position(0);

    testModule->sendMessage(movement, "server_respond");
    for(int i = 0; i < 11; ++i) {
        for(int i = 0; i < buses.size(); ++i) {
            buses[i]->set_position(buses[i]->position() + 0.1);
        }
        testModule->sendMessage(movement, "server_respond");
        QSignalSpy(testModule, SIGNAL(messageReceivedSignal())).wait(1000);

    }

    for(int k = 0; k <  route_info->station_size() * 10 * 3; ++k) {
        for(int i = 0; i < buses.size(); ++i) {
            buses[i]->set_position(buses[i]->position() + 0.1);
            if(buses[i]->position() > (route_info->station_size()-1 - 0.2)) {
                buses[i]->set_position(0.1);
                for(int j = 0; j < buses.size(); ++j) {
                    buses[j]->set_route_order(buses[j]->route_order() + 1);
                }
                buses[i]->set_route_order(1);
            }
        }

        testModule->sendMessage(movement, "server_respond");
        QSignalSpy(testModule, SIGNAL(messageReceivedSignal())).wait(1000);
    }

}

