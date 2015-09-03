#include "test.h"
#include "skel_message.pb.h"
#include "test_message.pb.h"
#include "geo_message.pb.h"
#include "sender_message.pb.h"
#include "tests.h"

Q_LOGGING_CATEGORY(TESTC, "test_module")

TEST(Habr, cut)
{
    qDebug() << "123";
}

static TestModule *instance = NULL;

TestModule::TestModule(QObject *parent)
{
    setParent(parent);

    this->name = "test_instance";

    instance = this;

    qCDebug(TESTC, "hello,world");
}

void TestModule::start()
{
    sendTestMessage();
}

void TestModule::stop()
{

}

QStringList TestModule::getPubTopics()
{
    QStringList topics;
    topics << "hello1";
}

void TestModule::sendMessage(indigo::pb::internal_msg &msg, QString topic)
{
    publish(msg, topic);
}

void TestModule::respond(QString topic, ::indigo::pb::internal_msg &message)
{
    // TODO
    qCDebug(TESTC) << "received a message of topic " << topic;
    emit messageReceivedSignal();

    if (message.HasExtension(::indigo::pb::skel_message::skel_message_in)) {
        ::indigo::pb::skel_message msg = message.GetExtension(::indigo::pb::skel_message::skel_message_in);

        qCDebug(TESTC) << "data is: " << msg.data();
    }

    if (message.HasExtension(::indigo::pb::indigo_geo::geo_coords_in)) {
        ::indigo::pb::indigo_geo msg = message.GetExtension(::indigo::pb::indigo_geo::geo_coords_in);

        qCDebug(TESTC) << "got geo message: " << msg.latitude() << " " << msg.longitude();
    }
}

void TestModule::sendTestMessage()
{
    //publish("");

    ::indigo::pb::internal_msg positionMessage;
    ::indigo::pb::indigo_geo *geo = positionMessage.MutableExtension(::indigo::pb::indigo_geo::geo_coords_in);
    geo->set_latitude(5.0);
    geo->set_longitude(6.0);
    geo->mutable_unixtime()->set_time(555);

    publish(positionMessage,name);

}

void TestModule::subscribeTopic(QString topic)
{
    qCDebug(TESTC) << "test module subscribe: " << topic;
    subscribe(topic);
}
