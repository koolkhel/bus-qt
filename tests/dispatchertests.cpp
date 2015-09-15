#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>

#include <unistd.h>

#include "indigo.h"
void foo(QtMsgType, const QMessageLogContext &, const QString &) {}

TEST(disptest, sanity) {
    ASSERT_TRUE(qApp->thread() == QThread::currentThread());

    qInstallMessageHandler(foo);
    // запуск контекстов и т.д.
    Dispatcher *dispatcher = new Dispatcher();

    usleep(1000 * 1000);

    QStringList c;
    c << "[modules]"
      << "test_instance=test_module"
      << "skel_instance=skel"
      << "[test_instance]"
      << "[skel_instance]";

    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    ASSERT_TRUE(testModule != NULL);

    Module *skelModule = dispatcher->getModuleInstances().value("skel_instance");

    ASSERT_TRUE(skelModule != NULL);

    dispatcher->startAll();

    usleep(2 * 1000 * 1000);

    QSignalSpy mySpy(testModule, SIGNAL(messageReceivedSignal()));

    testModule->subscribeTopic("skel");


    usleep(2000 * 1000);

    qApp->processEvents();
    qApp->processEvents();
    qApp->processEvents();
    qApp->processEvents();

    usleep(1000);

    for (int i = 0; i < 100000; i++) {
        skelModule->start();

        qApp->processEvents();
        qApp->processEvents();
    }



    // class GPSModule : protected Module
    //GPSModule *module = new GPSModule(simulation);
    //GPSModule *module = new GPSModule();


    //dispatcher->addModule(module, "GPS");

    // TestModule : protected Module
    //TestModule *test_module = new TestModule;
   // dispatcher->addModule(test_module, "test");
    // ждем вот это
    //test->test_subscribe("GPS_data_raw"); // != название модуля

    // подписаться можно только у тестового модуля, интерфейс остальных пока осторожно скрываем
   // QSignalSpy spy(test_module, SIGNAL(messageReceived(QByteArray)));

    // gps, мы здеся
    //module->stxxxxxxx<art_simulation(5.0, 6.0); // async
    // поработай
    //test_module->test_step(); // sync

    //spy.wait(200);
    //data = spy.at(0);

    //protobuf_gen_code = dispatcher->parseData(topic, data); // знает, какие топики как должны парситься
    // T parseData<T>()

    //ASSERT_EQ(protobuf_gen_code.latitude, 5.0);
    //ASSERT_EQ(protobuf_gen_code.longitude, 6.0);
}

TEST(dispatcher, creation) {
    Dispatcher *dispatcher = new Dispatcher();

    dispatcher->initializeAll("testconfig.ini");

    delete dispatcher;
}
