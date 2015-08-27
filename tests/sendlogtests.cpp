#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <QTestEventLoop>

#include <QtSql>

#include "sender_message.pb.h"
#include "geo_message.pb.h"
#include "blackbox_message.pb.h"

TEST(sendlog, udp_read) {
    QStringList c;
    c << "[modules]"
      << "sendlog_instance=sendlog"
      << "[sendlog_instance]"
      << "logport=45000";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    QTestEventLoop loop;
    loop.enterLoop(100);


}

