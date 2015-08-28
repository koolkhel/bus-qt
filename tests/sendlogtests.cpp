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
      << "logPort=45000"
      << "serverPort=45001";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    QTestEventLoop loop;
    loop.enterLoop(100);
    // nc -l -u 45001 & echo -n “foo” | nc -4u -w1 127.0.0.1 45000
    // Для теста начинаем слушать в фоне  сообщения
    // И затем отправляем сообщение
}

