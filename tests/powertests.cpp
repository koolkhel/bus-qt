

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

TEST(power, start) {

    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;
    c << "[modules]"
      << "S1=io"
      << "S2=io"
      << "ACPG=io"
      << "power_instance=power"
      << "test_instance=test_module"
      << "[S1]"
      << "id=1"
      << "device=/home/yury/tmp1.txt"
      << "[S2]"
      << "id=2"
      << "device=/home/yury/tmp2.txt"
      << "[ACPG]"
      << "id=3"
      << "device=/home/yury/tmp3.txt"
      << "[power_instance]"
      << "S1_ID=1"
      << "S2_ID=2"
      << "ACPG_ID=3"
      << "[test_instance]";

    dispatcher->initializeAll(c);
    for(int i = 1; i < 4; ++i) {
        QFile file(QString("/home/yury/tmp%1.txt").arg(i));
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << 1;
        file.close();
    }

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    dispatcher->startAll();

    testModule->subscribeTopic("power");
    QSignalSpy spy(testModule,  SIGNAL(messageReceivedSignal()));

    spy.wait(1000*1000*10);
    spy.wait(1000);
    spy.wait(1000);

    qDebug() << spy.count(); //почему не всегда 3?
    delete dispatcher;


}

