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
#include "Publisher.hpp"
#include "Subscriber.hpp"

void enableSignalHandling();
void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63);

QThread* makeExecutionThread(nzmqt::samples::SampleBase& sample)
{
    QThread* thread = new QThread;
    sample.moveToThread(thread);

    bool connected = false;
    connected = QObject::connect(thread, SIGNAL(started()), &sample, SLOT(start()));         Q_ASSERT(connected);
    connected = QObject::connect(&sample, SIGNAL(finished()), thread, SLOT(quit()));         Q_ASSERT(connected);
    connected = QObject::connect(&sample, SIGNAL(finished()), &sample, SLOT(deleteLater())); Q_ASSERT(connected);
    connected = QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));   Q_ASSERT(connected);

    return thread;
}

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

TEST(logging, tests) {

    QString filter = "GPS";
    ZeroMQPublisher *publisher = new ZeroMQPublisher("tcp://127.0.0.1:8080",filter);
    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber();
    subscriber->subscribeTo("tcp://127.0.0.1:8080",filter);

    publisher->sendMessage("Hello");
      /* try {
           QScopedPointer<nzmqt::ZMQContext> context(nzmqt::createDefaultContext());

           nzmqt::samples::pubsub::Publisher* publisher = new nzmqt::samples::pubsub::Publisher(*context, "inproc://pubsub", "ping");
           QSignalSpy spyPublisherPingSent(publisher, SIGNAL(pingSent(const QList<QByteArray>&)));
           QSignalSpy spyPublisherFailure(publisher, SIGNAL(failure(const QString&)));
           QSignalSpy spyPublisherFinished(publisher, SIGNAL(finished()));

           QThread* publisherThread = makeExecutionThread(*publisher);
           QSignalSpy spyPublisherThreadFinished(publisherThread, SIGNAL(finished()));

           nzmqt::samples::pubsub::Subscriber* subscriber = new nzmqt::samples::pubsub::Subscriber(*context, "inproc://pubsub", "ping");
           QSignalSpy spySubscriberPingReceived(subscriber, SIGNAL(pingReceived(const QList<QByteArray>&)));
           QSignalSpy spySubscriberFailure(subscriber, SIGNAL(failure(const QString&)));
           QSignalSpy spySubscriberFinished(subscriber, SIGNAL(finished()));

           QThread* subscriberThread = makeExecutionThread(*subscriber);
           QSignalSpy spySubscriberThreadFinished(subscriberThread, SIGNAL(finished()));

           //
           // START TEST
           //

           context->start();

           publisherThread->start();
           QTest::qWait(500);
           subscriberThread->start();

           QTimer::singleShot(6000, publisher, SLOT(stop()));
           QTimer::singleShot(6000, subscriber, SLOT(stop()));

           QTest::qWait(8000);

           //
           // CHECK POSTCONDITIONS
           //

           qDebug() << "Publisher pings sent:" << spyPublisherPingSent.size();
           qDebug() << "Subscriber pings received:" << spySubscriberPingReceived.size();

           QCOMPARE(spyPublisherFailure.size(), 0);
           QCOMPARE(spySubscriberFailure.size(), 0);

           QVERIFY2(spyPublisherPingSent.size() > 3, "Server didn't send any/enough pings.");
           QVERIFY2(spySubscriberPingReceived.size() > 3, "Client didn't receive any/enough pings.");

           QVERIFY2(qAbs(spyPublisherPingSent.size() - spySubscriberPingReceived.size()) < 3, "Publisher and subscriber communication flawed.");

           QCOMPARE(spyPublisherFinished.size(), 1);
           QCOMPARE(spySubscriberFinished.size(), 1);

           QCOMPARE(spyPublisherThreadFinished.size(), 1);
           QCOMPARE(spySubscriberThreadFinished.size(), 1);
       }
       catch (std::exception& ex)
       {
           QFAIL(ex.what());
       }*/

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
