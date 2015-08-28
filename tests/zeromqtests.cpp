#include <gtest/gtest.h>

#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/text_format.h>

#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"
#include "context.h"
#include "zhelpers.h"
#include "proxy.h"

#include "events_message.pb.h"
#include "geo_message.pb.h"
#include "sender_message.pb.h"


#define ZMQ_PUB_STR "tcp://127.0.0.1:8080"
#define ZMQ_SUB_STR "tcp://127.0.0.1:8080"
const QString ZMQ_PUB_STR_SECOND = "tcp://127.0.0.1:8081";


void closeSockets(ZeroMQSubscriber *subscriber, ZeroMQPublisher *publisher, nzmqt::ZMQContext *context)
{
    subscriber->close();
    publisher->close();
    context->stop();
    usleep(100 * 1000);
}

TEST(ZMQ, testWTF)
{
    QObject obj;
    nzmqt::ZMQContext* context = nzmqt::createDefaultContext(&obj);

    ASSERT_TRUE(context != NULL);

    context->start();
    context->stop();
    usleep(100 * 1000);
}

TEST(ZMQ, ProtobufSendFilter)
{
    ::indigo::pb::indigo_msg message;
    ::indigo::pb::indigo_geo geo;
    ::indigo::pb::indigo_event myevent;

    geo.set_latitude(5.0);
    geo.set_longitude(6.0);
    geo.mutable_unixtime()->set_time(555);

    // код расширения берется из расширяющего класса. В нем записано название
    // поля из основного класса
    message.AddExtension(::indigo::pb::indigo_geo::geo_coords)->CopyFrom(geo);
    ASSERT_TRUE(message.HasExtension(::indigo::pb::indigo_geo::geo_coords))
            << "Geo coord extension failed to add";

    myevent.set_type(::indigo::pb::EVENT_NOTHING);
    myevent.mutable_time()->set_time(666);
    message.AddExtension(::indigo::pb::indigo_event::events)->CopyFrom(myevent);
    ASSERT_TRUE(message.HasExtension(::indigo::pb::indigo_event::events))
            << "Events extension failed to add";

    message.mutable_device_id()->set_least_significant_bits(5);
    message.mutable_device_id()->set_most_significant_bits(7);

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    bool result = false;
    int byte_size = message.ByteSize();
    result = message.SerializeToArray(buffer, sizeof(buffer));
    ASSERT_TRUE(result)
            << "unable to successfully serialize indigo_msg object";

    ::indigo::pb::indigo_msg message2;

    // здесь принципиально важно парсить столько, сколько ожидается длина сообщения
    // TRUE будет только если мы закончили разбор сообщения четко по границе входного буфера
    result = message2.ParseFromArray(buffer, byte_size);

    // Печаль, но почему-то нельзя понять, распарсили мы что-то или нет
    ASSERT_TRUE(result) << ".ParseFromArray() returned false. Perhaps. wrong message border";

    // проверка того, что установлены required поля
    ASSERT_TRUE(message2.IsInitialized())
            << "message not initialized; not enough required fields";

    ASSERT_EQ(message2.device_id().least_significant_bits(), 5)
            << "parsed data differs from sent data";
    ASSERT_EQ(message2.device_id().most_significant_bits(), 7)
            << "parsed data differs from sent data";;

    ASSERT_TRUE(message2.HasExtension(::indigo::pb::indigo_geo::geo_coords))
            << "Geo coord extension failed to parse after serialization";

    ::indigo::pb::indigo_geo geo2;
    geo2.CopyFrom(message2.GetRepeatedExtension(::indigo::pb::indigo_geo::geo_coords).Get(0));

    ASSERT_EQ(geo2.latitude(), 5.0)
            << "Wrong received latitude";
    ASSERT_EQ(geo2.longitude(), 6.0)
            << "Wrong received longitude";
    ASSERT_EQ(geo2.unixtime().time(), 555)
            << "Wrong received unixtime";

    ASSERT_TRUE(message2.HasExtension(::indigo::pb::indigo_event::events))
            << "Events extension failed to parse after serialization";
    ::indigo::pb::indigo_event event2;
    event2.CopyFrom(message2.GetRepeatedExtension(::indigo::pb::indigo_event::events).Get(0));

    ASSERT_EQ(event2.type(), ::indigo::pb::EVENT_NOTHING)
            << "Incorrect parsed event type";
    ASSERT_EQ(event2.time().time(), 666)
            << "Incorrect parsed event time";

    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();


    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    QString filter = "1";
    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);

    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    context->start();

    QByteArray byteArray(message.SerializeAsString().c_str());
    nzmqt::ZMQMessage *msg = new nzmqt::ZMQMessage(byteArray);
    publisher->sendMessage(msg->toByteArray());

    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);
    spySubscriberMessageRecieved.wait(100);

    ASSERT_TRUE(spyPublisherMessageSent.size() > 0)<< "Server didn't send any/enough messages.";
    ASSERT_TRUE(spySubscriberMessageRecieved.size() > 0) << "Client didn't receive any/enough messages.";


    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

  //  ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }
    subscriber->close();
    publisher->close();
    context->stop();
    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);

}

TEST(ZMQ, PROXY)
{
    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;
    QThread *secondPublisherThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQPublisher *secondPublisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
    secondPublisher->moveToThread(secondPublisherThread);
    secondPublisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    QString filter = "Bear";
    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);

    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    nzmqt::ZMQSocket::proxyFromTo(publisher->getPublisher(), subscriber->getSubscriber());

    usleep(100 * 1000);
    context->start();

    publisher->sendMessage("Hello","B");


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
    usleep(100 * 1000);

}

TEST(ZMQ, FromTestSources) {

    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    //nzmqt::pubsub::Publisher *publisher = new nzmqt::pubsub::Publisher(context, ZMQ_PUB_STR);
    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
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

    spyPublisherMessageSent.wait(100);
    spySubscriberMessageRecieved.wait(100);
    usleep(100 * 1000);


   ASSERT_TRUE(spyPublisherMessageSent.size() > 0) << "Server didn't send any/enough messages.";
   ASSERT_TRUE(spySubscriberMessageRecieved.size() > 0) << "Client didn't receive any/enough messages.";

    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

    //ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }

    subscriber->close();
    publisher->close();
    context->stop(); //в деструктор dispatcher
    usleep(100 * 1000);
    //ASSERT_TRUE(spyFinishedContext.size() > 0) <<"Finished";

    /*
    while(1)
    {
       if(spyFinishedContext.size() > 0)
       {
           qDebug() << spyFinishedContext.size();
            break;
       }

    }*/
}


TEST(ZMQ, Qts) {

    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
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
    usleep(100 * 1000);

}

TEST(ZMQ, 2subs2Pubs) {
    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;
    QThread *publisherSecondThread = new QThread;
    QThread *secondSubscrberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQPublisher *secondPublisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR_SECOND));
    secondPublisher->moveToThread(publisherSecondThread);
    publisherSecondThread->start();
    usleep(100 * 1000);


    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    usleep(100 * 1000);


    ZeroMQSubscriber *secondSubscriber = new ZeroMQSubscriber(context);
    secondSubscriber->moveToThread(secondSubscrberThread);
    secondSubscrberThread->start();

    usleep(100 * 1000);


    QString filter = "";
    subscriber->subscribeTo(QString(ZMQ_PUB_STR_SECOND), filter);
    secondSubscriber->subscribeTo(QString(ZMQ_PUB_STR),filter);

    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySecondPublisherMessageSent(secondPublisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    context->start();

    secondPublisher->sendMessage("Hello");
    publisher->sendMessage("Hello");

    usleep(100 * 1000);
    spySecondPublisherMessageSent.wait(100);

    ASSERT_TRUE(spySecondPublisherMessageSent.size() > 0) << "Second server didn't send any messages";
    ASSERT_TRUE(spyPublisherMessageSent.size() > 0) << "Server didn't send any/enough messages.";
    ASSERT_TRUE(spySubscriberMessageRecieved.size() > 0) << "Client didn't receive any/enough messages.";

    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

  //  ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }
    context->stop();
    subscriber->close();
    publisher->close();
    secondPublisher->close();
    usleep(100 * 1000);
}

TEST(ZMQ, 1publisher_3subscribers)
{
    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;
    QThread *newSubscriberThread = new QThread;
    QThread *thirdSubscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *secondSubscriber = new ZeroMQSubscriber(context);
    secondSubscriber->moveToThread(newSubscriberThread);
    newSubscriberThread->start();

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    ZeroMQSubscriber *thirdSubscriber = new ZeroMQSubscriber(context);
    thirdSubscriber->moveToThread(thirdSubscriberThread);
    thirdSubscriberThread->start();

    QString filter = "";
    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);
    secondSubscriber->subscribeTo(QString(ZMQ_SUB_STR),filter);
    thirdSubscriber->subscribeTo(QString(ZMQ_SUB_STR),filter);


    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));
    QSignalSpy spySecondSubscriberMessageRecieved(secondSubscriber,SIGNAL(recieved()));
    QSignalSpy spyThridSubscriberMessageRecieved(thirdSubscriber,SIGNAL(recieved()));

    context->start();

    publisher->sendMessage("Hello");

    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);

   ASSERT_TRUE(spyPublisherMessageSent.size() > 0) << "Server didn't send any/enough messages.";
   ASSERT_TRUE(spySubscriberMessageRecieved.size() > 0) << "Client didn't receive any/enough messages.";
   ASSERT_TRUE(spySecondSubscriberMessageRecieved.size() > 0) <<"Client didn't receive any/enough messages.";
   ASSERT_TRUE(spyThridSubscriberMessageRecieved.size() > 0) <<"Client didn't receive any/enough messages.";


    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

  //  ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }

    context->stop();
    subscriber->close();
    publisher->close();
    secondSubscriber->close();
    thirdSubscriber->close();

    context->stop();
    usleep(100 * 1000);
}

TEST(ZMQ, 2publisher_3_subscribers)
{
    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *secondPublisherThread = new QThread;
    QThread *subscriberThread = new QThread;
    QThread *newSubscriberThread = new QThread;
    QThread *thirdSubscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();

    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQPublisher *secondPublisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR_SECOND));
    secondPublisher->moveToThread(secondPublisherThread);
    secondPublisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *secondSubscriber = new ZeroMQSubscriber(context);
    secondSubscriber->moveToThread(newSubscriberThread);
    newSubscriberThread->start();

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    ZeroMQSubscriber *thirdSubscriber = new ZeroMQSubscriber(context);
    thirdSubscriber->moveToThread(thirdSubscriberThread);
    thirdSubscriberThread->start();

    QString filter = "";

    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);
    secondSubscriber->subscribeTo(QString(ZMQ_PUB_STR_SECOND),filter);
    thirdSubscriber->subscribeTo(QString(ZMQ_SUB_STR),filter);


    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySecondPublisherMessageSent(secondPublisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));
    QSignalSpy spySecondSubscriberMessageRecieved(secondSubscriber,SIGNAL(recieved()));
    QSignalSpy spyThridSubscriberMessageRecieved(thirdSubscriber,SIGNAL(recieved()));

    context->start();

    publisher->sendMessage("Hello");
    secondPublisher->sendMessage("Hello 2");

    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);
    spySecondPublisherMessageSent.wait(100);

    ASSERT_TRUE(spyPublisherMessageSent.size() > 0) << "Server didn't send any/enough messages.";
    ASSERT_TRUE(spySecondPublisherMessageSent.size() > 0 ) << "Server didn't send any/enough messages.";
    ASSERT_TRUE(spySubscriberMessageRecieved.size() > 0) << "Client didn't receive any/enough messages.";
    ASSERT_TRUE(spySecondSubscriberMessageRecieved.size() > 0) <<"Client didn't receive any/enough messages.";
    ASSERT_TRUE(spyThridSubscriberMessageRecieved.size() > 0) <<"Client didn't receive any/enough messages.";


    QList<QVariant> params = spySubscriberMessageRecieved.takeFirst();

  //  ASSERT_TRUE(params.size() > 0) << "no signals received";

    if (params.size() > 0) {
        ASSERT_TRUE(params.at(0).toString() == "Hello") << "Other data received";
    }

    context->stop();
    subscriber->close();
    publisher->close();
    usleep(100 * 1000);
}
TEST(ZMQ, QtWithProxy) {
    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();


    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    zmq_proxy(publisher->getPublisher(),subscriber->getSubscriber(),NULL);


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
    usleep(100 * 1000);
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

    publisher.close();
    subscriber.close();
    context.close();

    usleep(100 * 1000);

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

TEST(ZMQ, 100messages) {

    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();


    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
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

    for(int i=0; i<100; ++i)
    {
        publisher->sendMessage("Hello");
    }

    usleep(100 * 1000);
    spyPublisherMessageSent.wait(100);

   ASSERT_TRUE(spyPublisherMessageSent.size() == 100)<< "Server didn't send any/enough messages.";
   ASSERT_TRUE(spySubscriberMessageRecieved.size() ==100) << "Client didn't receive any/enough messages.";

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

TEST(ZMQ, TenThousand) {

    QThread *contextThread = new QThread;
    QThread *publisherThread = new QThread;
    QThread *subscriberThread = new QThread;

    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    context->moveToThread(contextThread);

    contextThread->start();


    ZeroMQPublisher *publisher = new ZeroMQPublisher(context,QString(ZMQ_PUB_STR));
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    usleep(100 * 1000);

    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subscriberThread);
    subscriberThread->start();

    zmq_proxy(publisher->getPublisher(),subscriber->getSubscriber(),NULL);


    QString filter = "";
    subscriber->subscribeTo(QString(ZMQ_SUB_STR), filter);

    usleep(100 * 1000);

    QSignalSpy spyPublisherMessageSent(publisher, SIGNAL(messageSend(QByteArray)));
    QSignalSpy spySubscriberMessageRecieved(subscriber,SIGNAL(recieved()));

    context->start();

    for(int i=0; i<10000; ++i)
    {
        publisher->sendMessage("Hello");
    }

    usleep(100 * 100000);
   // spyPublisherMessageSent.wait(10000);

    //ASSERT_TRUE(spyPublisherMessageSent.size() == 10000)<< "Server didn't send any/enough messages.";
    //ASSERT_TRUE(spySubscriberMessageRecieved.size() ==10000) << "Client didn't receive any/enough messages.";

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

TEST(ZMQ, C_10th) {
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

    int s = 0;
    for(int i=0; i<10000; i++)
    {
       int a = s_send (publisher, update);
       s = s+ a;
    }

    ASSERT_TRUE(s == 10000);

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

