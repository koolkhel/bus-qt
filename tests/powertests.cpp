

#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <unistd.h>
#include <QFile>
#include <QTextStream>

#include "io_message.pb.h"
using namespace indigo::pb;
TEST(power, start) {

    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;
    c << "[modules]"
      << "power_instance=power"
      << "test_instance=test_module"
      << "[power_instance]"
      << "S1_ID=1"
      << "S2_ID=2"
      << "ACPG_ID=3"
      << "powerTopic=power"
      << "inputTopics=io_in"
      << "[test_instance]";

    dispatcher->initializeAll(c);


    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    dispatcher->startAll();
    QTestEventLoop loop;

    loop.enterLoop(10);
    testModule->subscribeTopic("power");
    QSignalSpy spy(testModule,  SIGNAL(messageReceivedSignal()));
    internal_msg ioMessage;
    io_message *io = ioMessage.MutableExtension(io_message::io_message_in);
    io->mutable_time()->set_time(QTime::currentTime().msecsSinceStartOfDay());
    for(int i = 1; i <= 3; ++i) {
        io->set_io_id(static_cast< io_message_IO_id >(i));
        for(int j = 0; j <= 1; ++j) {
            io->set_value(j);
            for(int k = 0; k <= 1; ++k) {
                io->set_bounce(static_cast<io_message_bounce_state> (k));
                testModule->sendMessage(ioMessage, "io_in");
                loop.enterLoopMSecs(400);
            }
        }
    }
    loop.enterLoop(5);
    qDebug() << spy.count();

    delete dispatcher;


}

