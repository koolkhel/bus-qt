#include "test.h"
#include "skel_message.pb.h"
#include "test_message.pb.h"
#include "geo_message.pb.h"
#include "sender_message.pb.h"


Q_LOGGING_CATEGORY(TESTC, "test_module")

TestModule::TestModule(QObject *parent)
{
    setParent(parent);
    this->name = "test_instance";
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

    ::indigo::pb::indigo_msg message;
    ::indigo::pb::indigo_geo geo;
    geo.set_latitude(5.0);
    geo.set_longitude(6.0);
    geo.set_unixtime(555);

    message.AddExtension(::indigo::pb::indigo_geo::geo_coords)->CopyFrom(geo);

    publish(message,name);

}

void TestModule::subscribeTopic(QString topic)
{
    qCDebug(TESTC) << "test module subscribe: " << topic;
    subscribe(topic);
}
