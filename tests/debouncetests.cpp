
#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <unistd.h>

TEST(debounce, start) {

    Dispatcher *dispatcher = new Dispatcher();

    const int test_count = 10;

    QStringList c;
    c << "[modules]"
      << "debounce_instance=debounce"
      << "test_instance=test_module"
      << "[debounce_instance]"
      << "[test_instance]";

    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    dispatcher->startAll();

    testModule->subscribeTopic("spam");
    ::indigo::pb::internal_msg msg;

    QSignalSpy spy(testModule, SIGNAL(messageReceivedSignal()));
    for (int i = 0; i < test_count; i++) {
        testModule->sendMessage(msg, "skel");
        spy.wait(2000);
        qApp->processEvents();
        qApp->processEvents();

    }

    qDebug() << spy.count();

    delete dispatcher;


}
