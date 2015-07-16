
#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <unistd.h>

TEST(io, start) {

    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;
    c << "[modules]"
      << "io_instance=io"
      << "test_instance=test_module"
      << "debounce_instance=debounce"
      << "[io_instance]"
      << "devices=/home/moka/Projects/debounce/modules/io/io.json"
      << "[test_instance]"
      << "[debounce_instance]"
      << "inputTopics=io";

    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    dispatcher->startAll();
    QSignalSpy spy(testModule,  SIGNAL(messageReceivedSignal()));
    spy.wait(10000);
    delete dispatcher;


}

