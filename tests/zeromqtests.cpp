#include <gtest/gtest.h>

#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

#include <google/protobuf/text_format.h>

#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

#include "testclass.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"


#include "Publisher.hpp"
#include "Subscriber.hpp"

#include "context.h"
#include "zhelpers.h"

#define ZMQ_PUB_STR "tcp://127.0.0.1:8080"
#define ZMQ_SUB_STR "tcp://127.0.0.1:8080"

TEST(ZMQ, testWTF) {
    QObject obj;
    nzmqt::ZMQContext* context = nzmqt::createDefaultContext(&obj);

    ASSERT_TRUE(context != NULL);

    context->start();
    context->stop();
}

TEST(ZMQ, FromTestSources) {

    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    //nzmqt::pubsub::Publisher *publisher = new nzmqt::pubsub::Publisher(context, ZMQ_PUB_STR);
    ZeroMQPublisher *publisher = new ZeroMQPublisher(QString(ZMQ_PUB_STR), context);
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    QString filter = "";
    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);

    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    context->start();

    publisher->sendMessage("Hello");

    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);

   ASSERT_TRUE(spyPublisherMessageSent.size() > 0) << "Server didn't send any/enough messages.";
   ASSERT_TRUE(spySubscriberMessageRecieved.size() > 0) << "Client didn't receive any/enough messages.";

    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

    //ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }

    subscriber->close();
    publisher->close();
    context->stop();

    usleep(100 * 1000);
}


TEST(ZMQ, Qts) {

    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    ZeroMQPublisher *publisher = new ZeroMQPublisher(QString(ZMQ_PUB_STR), context);
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    QString filter = "";
    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);

    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    context->start();
    for(int i=0; i<100;i++)
    {
        publisher->sendMessage("Hello");
    }
    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);

   ASSERT_TRUE(spyPublisherMessageSent.size() == 100) << "Server didn't send any/enough messages.";
   ASSERT_TRUE(spySubscriberMessageRecieved.size() == 100) << "Client didn't receive any/enough messages.";

    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

  //  ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }

    subscriber->close();
    publisher->close();
    context->stop();
}

TEST(ZMQ, Qt50) {
    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    ZeroMQPublisher *publisher = new ZeroMQPublisher(QString(ZMQ_PUB_STR), context);
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    QString filter = "";
    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);

    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    context->start();
    for(int i=0; i<50;i++)
    {
        publisher->sendMessage("Hello");
    }
    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);

   ASSERT_TRUE(spyPublisherMessageSent.size() == 50) << "Server didn't send any/enough messages.";
   ASSERT_TRUE(spySubscriberMessageRecieved.size() == 50) << "Client didn't receive any/enough messages.";

    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

  //  ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }

    subscriber->close();
    publisher->close();
    context->stop();

    usleep(100 * 1000);
}

TEST(ZMQ, QtWithProxy) {
    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();


    ZeroMQPublisher *publisher = new ZeroMQPublisher(QString(ZMQ_PUB_STR), context);
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    zmq_proxy(publisher,subscriber,NULL);


    QString filter = "";
    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);

    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    context->start();

    publisher->sendMessage("Hello");

    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);

   ASSERT_TRUE(spyPublisherMessageSent.size() > 0) << "Server didn't send any/enough messages.";
   ASSERT_TRUE(spySubscriberMessageRecieved.size() > 0) << "Client didn't receive any/enough messages.";

    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

  //  ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }

    subscriber->close();
    publisher->close();
    context->stop();
}

TEST(ZMQ, CPLUS) {
    #define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind(ZMQ_PUB_STR);

    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect(ZMQ_SUB_STR);

    zmq::message_t message(20);
    int temperature;
    temperature = within (215) - 80;
    snprintf ((char *) message.data(), 20 ,
        "%05d", temperature);
    fprintf(stdout, "%s\n", (char *) message.data());

    const char *filter = "";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));

    usleep(100 * 1000);

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

    subscriber.close();
    publisher.close();
}



TEST(ZMQ, C) {
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, ZMQ_PUB_STR);
    ASSERT_TRUE (rc == 0);

    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rec = zmq_connect (subscriber, ZMQ_SUB_STR);
    ASSERT_TRUE (rec == 0);

    //  Subscribe to zipcode, default is NYC, 10001
    char *filter = "";
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,
                         filter, strlen (filter));

    usleep(100 * 1000);

    long total_temp = 0;
    //  Send message to all subscribers
    char update [20];
    sprintf (update, "%05d", 2);

    int send = s_send (publisher, update);

    ASSERT_TRUE(send > 0);

    ASSERT_TRUE (rec == 0);

    char *string = s_recv (subscriber);

    ASSERT_TRUE(strlen(string) > 0);

    ASSERT_STREQ(string, "00002");

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

