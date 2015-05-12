#include <gtest/gtest.h>

#include "testclass.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

#include "indigologger.h"
#include "loggertester.h"
#include <QtNetwork/QTcpSocket>

#include <QDebug>

#include <QTest>

#include <QSignalSpy>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

#include <google/protobuf/text_format.h>
#include "context.h"

void enableSignalHandling();
void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63);

TEST(logging, testLog) {
    LoggerTester tester;
    qInstallMessageHandler(indigoMessageHandler);

    QString lastStr;

    lastStr = QString("fuck you");
    qDebug() << lastStr;
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));

    lastStr = QString("hello, world!");
    qDebug () << lastStr;
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));

    lastStr = QString("wtf %1").arg(5);
    qCritical(qPrintable(lastStr));
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));
}

TEST(logging, categories) {
    LoggerTester tester;
    qInstallMessageHandler(indigoMessageHandler);

    qCDebug(GSM, "Gsm test");
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.contains("indigo.gsm"));

    qCWarning(ZMQ, "ZMQ not working");
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.contains("indigo.zmq"));
}

TEST(logging, configuration) {
    LoggerTester tester;
    qInstallMessageHandler(indigoMessageHandler);

    qCDebug(ZMQ, "Gsm test");
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains("Gsm test"));

    QSignalSpy spy(instance, SIGNAL(configurationChanged()));

    tester.putConf("indigo.gsm=false");

    spy.wait(500000);

    ASSERT_TRUE(spy.size() != 0);
    QList<QVariant> signal = spy.at(0);

    qCWarning(ZMQ, "ZMQ not working");
    qCDebug(GSM, "Gsm test");
    tester.wait();
    ASSERT_FALSE(tester.lastMessage.simplified().contains("Gsm test"));
}

TEST(Zmq, testWTF) {
    QObject obj;
    nzmqt::ZMQContext* context = nzmqt::createDefaultContext(&obj);
    context->start();
    context->stop();
}

TEST(Zmq, tests) {
    QString address = "tcp://127.0.0.1:8887";

    QString filter = "GPS";
    qInstallMessageHandler(indigoMessageHandler);
    ZeroMQPublisher *publisher = new ZeroMQPublisher(address,filter);

    ZeroMQSubscriber *subscriber1 = new ZeroMQSubscriber;
    subscriber1->subscribeTo(address,filter);


    QSignalSpy spy(subscriber1,SIGNAL(recieved()));
    spy.wait(500);

    ZeroMQSubscriber *subscriber2 = new ZeroMQSubscriber;
    subscriber2->subscribeTo(address,filter);

    publisher->sendMessage("Hello");

    spy.wait(500);

    ASSERT_TRUE(spy.size() != 0);
}

int main(int argc, char **argv) {
    enableSignalHandling();
    QCoreApplication app(argc, argv);

    int result = 0;
    try {
        ::testing::InitGoogleTest(&argc, argv);
        result = RUN_ALL_TESTS();
    } catch (std::exception &e) {
        std::cerr << e.what();
    }

    return result;
}
