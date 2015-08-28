
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

TEST(io, read) {
    int TestCount = 100*1000;

    Dispatcher *dispatcher = new Dispatcher();

    QStringList c;
    c << "[modules]"
       << "io_instance=io"
       << "test_instance=test_module"
       << "[io_instance]"
       << "inputTopic=io_in"
       << "device=/home/yury/tmp.txt"
       << "timeout=20"
       << "[test_instance]";
    QFile file("/home/yury/tmp.txt");
    file.open(QIODevice::WriteOnly);

    QTextStream stream(&file);

    stream << 1;
    file.close();

    dispatcher->initializeAll(c);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));
    QSignalSpy spy(testModule,  SIGNAL(messageReceivedSignal()));

    dispatcher->startAll();
    testModule->subscribeTopic("io_out");


    QTestEventLoop loop;
    loop.enterLoop(10);

    int blocked = spy.count();
    for(int i = 0; i  < TestCount; ++i) {
        if(!file.open(QIODevice::WriteOnly)) {
            qDebug() << "blocking";
            ++blocked;
        }
        stream << (i & 1);
        file.close();
        loop.enterLoopMSecs(37);
//fprintf(stderr, "%d\n", i);
    }

    qDebug() << spy.count() << blocked
                //Тут бывает какаято погрешность в 0:-2
                      <<( ((spy.count()-blocked )== TestCount) ?  "Everything seems Ok"
                                                                                                : "Hmmm hmmm look more careful");

    delete dispatcher;


}

