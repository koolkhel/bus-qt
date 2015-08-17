
#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <unistd.h>

#include "io_message.pb.h"

TEST(debounce, lethal) {

    Dispatcher *dispatcher = new Dispatcher();

    const int test_count = 10;

    QStringList c;
    c << "[modules]"
      << "debounce_instance=debounce"
      << "test_instance1=test_module"
      << "test_instance2=test_module"
      << "test_instance3=test_module"
      << "[debounce_instance]"
      << "inputTopic=io_in"
      << "bounceStartedTopic=bounce_started"
      << "limitTopic=lethal"
      << "filtredTopic=iof_in"
      << "timeout=100"
      << "id=3"
      << "[test_instance1]"
      << "[test_instance2]"
      << "[test_instance3]";

    dispatcher->initializeAll(c);

    TestModule *bncStarted = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance1"));
    TestModule *lethal = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance2"));
    TestModule *filtred = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance3"));

    dispatcher->startAll();

    bncStarted->subscribeTopic("bounce_started");
    lethal->subscribeTopic("lethal");
    filtred->subscribeTopic("iof_in");
    ::indigo::pb::internal_msg msg;
    ::indigo::pb::io_message  *bodyMessage =
            msg.MutableExtension(indigo::pb::io_message::io_message_in);

    bodyMessage->set_io_id(static_cast < ::indigo::pb::io_message_IO_id> (3));
    bodyMessage->set_value(1);
    bodyMessage->set_epoch(QTime::currentTime().msecsSinceStartOfDay());
    QSignalSpy spyStart(bncStarted, SIGNAL(messageReceivedSignal()));
    QSignalSpy spyLethal(lethal, SIGNAL(messageReceivedSignal()));
    QSignalSpy spyFiltred(filtred, SIGNAL(messageReceivedSignal()));
    for (int i = 0; i < test_count; i++) {
        bodyMessage->set_epoch(QTime::currentTime().msecsSinceStartOfDay());

        bncStarted->sendMessage(msg, "io_in");
        spyStart.wait(2000);
        qApp->processEvents();
        qApp->processEvents();

    }

    qDebug() << spyStart.count();

    delete dispatcher;

}


TEST(debounce, filtred) {

    Dispatcher *dispatcher = new Dispatcher();

    const int test_count = 10;

    QStringList c;
    c << "[modules]"
      << "debounce_instance=debounce"
      << "test_instance1=test_module"
      << "test_instance2=test_module"
      << "test_instance3=test_module"
      << "[debounce_instance]"
      << "inputTopic=io_in"
      << "bounceStartedTopic=bounce_started"
      << "limitTopic=lethal"
      << "filtredTopic=iof_in"
      << "timeout=100"
      << "id=3"
      << "[test_instance1]"
      << "[test_instance2]"
      << "[test_instance3]";

    dispatcher->initializeAll(c);

    TestModule *bncStarted = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance1"));
    TestModule *lethal = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance2"));
    TestModule *filtred = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance3"));

    dispatcher->startAll();

    bncStarted->subscribeTopic("bounce_started");
    lethal->subscribeTopic("lethal");
    filtred->subscribeTopic("iof_in");
    ::indigo::pb::internal_msg msg;
    ::indigo::pb::io_message  *bodyMessage =
            msg.MutableExtension(indigo::pb::io_message::io_message_in);

    bodyMessage->set_io_id(static_cast < ::indigo::pb::io_message_IO_id> (3));
    bodyMessage->set_value(1);
    bodyMessage->set_epoch(QTime::currentTime().msecsSinceStartOfDay());
    QSignalSpy spyStart(bncStarted, SIGNAL(messageReceivedSignal()));
    QSignalSpy spyLethal(lethal, SIGNAL(messageReceivedSignal()));
    QSignalSpy spyFiltred(filtred, SIGNAL(messageReceivedSignal()));
    bncStarted->sendMessage(msg, "io_in");

    for (int i = 0; i < test_count; i++) {
        spyStart.wait(2000);
        qApp->processEvents();
        qApp->processEvents();
    }

    qDebug() << spyFiltred.count();

    delete dispatcher;

}
