

#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <unistd.h>

TEST(power, start) {

    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;
    c << "[modules]"
      << "io_instance1=io"
      << "io_instance2=io"
      << "io_instance3=io"
      << "io_instance4=io"
      << "io_instance5=io"
      << "io_instance6=io"
      << "io_instance7=io"
      << "io_instance8=io"
      << "io_instance9=io"
      << "io_instance10=io"
      << "power_instance=power"
      << "test_instance=test_module"
      << "[io_instance1]"
      << "id=1"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance2]"
      << "id=2"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance3]"
      << "id=3"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance4]"
      << "id=4"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance5]"
      << "id=5"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance6]"
      << "id=6"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance7]"
      << "id=7"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance8]"
      << "id=8"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance9]"
      << "id=9"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[io_instance10]"
      << "id=10"
      << "device=/home/moka/Projects/debounce/modules/io/io.json"
      << "[power_instance]"
      << "devices=1,2,3,4,5,6,7,8,9,10"
      << "[test_instance]"
      << "[debounce_instance]"
      << "inputTopics=io";

    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    dispatcher->startAll();
        //testModule->subscribeTopic("io");
    QSignalSpy spy(testModule,  SIGNAL(messageReceivedSignal()));

    spy.wait(1000*1000*10);
    spy.wait(1000);
    spy.wait(1000);

    qDebug() << spy.count(); //почему не всегда 3?
    delete dispatcher;


}

