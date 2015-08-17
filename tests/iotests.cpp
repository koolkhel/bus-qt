
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

TEST(io, start) {

    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;
    c << "[modules]"
      << "io_instance=io"
      << "test_instance=test_module"
      << "[io_instance]"
      << "device=/home/yury/tmp.txt"
      << "[test_instance]"
      << "[debounce_instance]"
      << "inputTopics=io";
    QFile file("/home/yury/tmp.txt");
    file.open(QIODevice::WriteOnly);

    QTextStream stream(&file);

    stream << 1;
    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    dispatcher->startAll();
        testModule->subscribeTopic("io_out");
    QSignalSpy spy(testModule,  SIGNAL(messageReceivedSignal()));

    spy.wait(20000);
    spy.wait(1000);
    spy.wait(1000);
    stream.seek(0);
    stream << 0;
    spy.wait(5000);
    stream.seek(0);
    stream << 1;
    spy.wait(5000);

    qDebug() << spy.count(); //почему не всегда 3?
    delete dispatcher;


}

