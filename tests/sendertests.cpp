#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "gpsmodule.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>


#include <QtSql>

#include "sender_message.pb.h"
#include "geo_message.pb.h"
#include "blackbox_message.pb.h"

TEST(SENDER, load) {
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
