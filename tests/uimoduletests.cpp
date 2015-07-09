#include "dispatcher.h"
#include "module.h"


#include <QSignalSpy>

#include <gtest/gtest.h>

TEST(uitest, sanity) {
    // запуск контекстов и т.д.
    Dispatcher *dispatcher = new Dispatcher();

    usleep(1000 * 1000);

    QStringList c;
    c << "[modules]"
      << "test_instance=test_module"
      << "ui_instance=UI"
      << "[test_instance]"
      << "[ui_instance]";

    dispatcher->initializeAll(c);

    Module *uiModule = dispatcher->getModuleInstances().value("ui_instance");

    ASSERT_TRUE(uiModule != NULL);

    dispatcher->startAll();
    usleep(1000 * 1000);

    qApp->processEvents();
    qApp->processEvents();
    qApp->processEvents();
    qApp->processEvents();

    usleep(1000);

    for (int i = 0; i < 10000; i++) {
        uiModule->start();
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
