
#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <unistd.h>

#include "io_message.pb.h"
using namespace indigo::pb;

TEST(debounce, bounce) {

    Dispatcher *dispatcher = new Dispatcher();

    QFile file("/home/yury/tmp.txt");
    file.open(QIODevice::WriteOnly);

    QTextStream stream(&file);

    stream << 1;
    file.close();

    QStringList c;
    c << "[modules]"
      << "debounce_instance=debounce"
      << "io_instance=io"
      << "test_instance=test_module"
      << "[io_instance]"
      << "inputTopic=io_in"
      << "outputTopic=io_out"
      << "device=/home/yury/tmp.txt"
      << "id=3"
      << "[debounce_instance]"
      << "inputTopic=io_out"
      << "bounceTopic=bounce_started"
      << "filtredTopic=iof_out"
      << "timeout=100"
      << "id=3"
      << "[test_instance]";

    dispatcher->initializeAll(c);

    TestModule *bncStarted = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));
    QSignalSpy spy(bncStarted,  SIGNAL(messageReceivedSignal()));

    dispatcher->startAll();

    QTestEventLoop loop;

    loop.enterLoop(10);

    bncStarted->subscribeTopic("bounce_started");

    for(int i = 0; i  < 200; ++i) {
        if(file.open(QIODevice::WriteOnly)) {
            stream << (i & 1);
            file.close();
        }
        loop.enterLoopMSecs(31);
    }

    loop.enterLoop(2);

    qDebug() << spy.count();

    delete dispatcher;

}


TEST(debounce, without_io) {

    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;
    c << "[modules]"
      << "debounce_instance=debounce"
      << "test_instance=test_module"
      << "[debounce_instance]"
      << "inputTopic=io_out"
      << "bounceTopic=bounce_started"
      << "filtredTopic=iof_out"
      << "timeout=100"
      << "id=3"
      << "[test_instance]";

    dispatcher->initializeAll(c);

    TestModule *bncStarted = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));
    QSignalSpy spy(bncStarted,  SIGNAL(messageReceivedSignal()));

    dispatcher->startAll();

    QTestEventLoop loop;

    loop.enterLoop(10);
    bncStarted->subscribeTopic("iof_out");
    bncStarted->subscribeTopic("bounce_started");

    internal_msg ioMessage;
    io_message *io = ioMessage.MutableExtension(io_message::io_message_in);


    io->set_io_id(static_cast< io_message_IO_id >(3));
    io->mutable_time()->set_time(QTime::currentTime().msecsSinceStartOfDay());
    for(int i = 0; i < 200; ++i) {
        io->set_value(i % 2);
        bncStarted->sendMessage(ioMessage, "io_out");
        io->mutable_time()->set_time(QTime::currentTime().msecsSinceStartOfDay());
        loop.enterLoopMSecs(31);
    }
    loop.enterLoop(2);

    delete dispatcher;

}
/**/
