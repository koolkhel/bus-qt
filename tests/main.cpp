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
#include "zhelpers.h"

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

TEST(ZMQ, Qts) {

    QString filter = "GPS";
    ZeroMQPublisher *publisher = new ZeroMQPublisher("tcp://127.0.0.1:8080",filter);
    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber();
    subscriber->subscribeTo("tcp://127.0.0.1:8080",filter);
    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    publisher->sendMessage("Hello");

    QVERIFY2(spyPublisherMessageSent.size() > 3, "Server didn't send any/enough messages.");
    QVERIFY2(spySubscriberMessageRecieved.size() > 3, "Client didn't receive any/enough messages.");
}

TEST(ZMQ, CPLUS) {
    #define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind("tcp://*:5556");
    publisher.bind("ipc://weather.ipc");

    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");

    zmq::message_t message(20);
    int temperature;
    temperature = within (215) - 80;
    snprintf ((char *) message.data(), 20 ,
        "%05d", temperature);
    fprintf(stdout, "%s\n", message.data());

    const char *filter = "";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));

    sleep(1);

    long total_temp = 0;

    zmq::message_t update;
    int temperatureRecv;


    bool isSended = publisher.send(message);

    ASSERT_TRUE(isSended);


    bool isRecieved = subscriber.recv(&update);

    ASSERT_TRUE(isRecieved);

    std::istringstream iss(static_cast<char*>(update.data()));
    iss>> temperatureRecv;

    total_temp += temperatureRecv;
}



TEST(ZMQ, C) {
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    ASSERT_TRUE (rc == 0);

    sleep(1);

    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rec = zmq_connect (subscriber, "tcp://localhost:5556");
    ASSERT_TRUE (rec == 0);

    sleep(1);

    //  Subscribe to zipcode, default is NYC, 10001
    char *filter = "";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,
                         filter, strlen (filter));

    sleep(1);

    long total_temp = 0;
    //  Send message to all subscribers
    char update [20];
    sprintf (update, "%05d", 2);

    int send = s_send (publisher, update);

    sleep(1);

    ASSERT_TRUE(send > 0);

    ASSERT_TRUE (rec == 0);

    char *string = s_recv (subscriber);

    ASSERT_TRUE(strlen(string) > 0);

    int zipcodeRecv;
    sscanf (string, "%d",
        &zipcodeRecv);
    total_temp += zipcodeRecv;
    free (string);
    fprintf(stderr, "OK!\n");


    zmq_close (subscriber);
    zmq_close (publisher);
    zmq_ctx_destroy (context);


}





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
