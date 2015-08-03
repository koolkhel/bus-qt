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
      << "[ui_instance]";

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
    testModule->subscribeTopic("server_data");

    ::indigo::pb::internal_msg msg;

    ::indigo::pb::route_info *route_info = msg.MutableExtension(::indigo::pb::route_info::route_info_in);
    route_info->set_bus_number("H200EM");
    route_info->set_route_name("2");

    ::indigo::pb::schedule_station *station = route_info->add_station();
    station->set_station_name("Конечная");

    ::indigo::pb::station_visit_schedule_time *visit_time = station->add_schedule_times();
    visit_time->set_visit_time(5 * 60);
    visit_time->set_daytime_start(0);
    visit_time->set_daytime_end(60 * 60 * 24);

    testModule->sendMessage(msg, "server_data");

    qApp->processEvents();
    usleep(1000 * 1000);
    qApp->processEvents();
    usleep(1000 * 1000);
    qApp->processEvents();

    for (int j = 0; j < 10; j++) {
        usleep(1000 * 1000);

        for (int i = 0; i < 20000; i++) {
            qApp->processEvents();
            usleep(1000);
        }
    }

}
