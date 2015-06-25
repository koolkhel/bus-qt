#include "test.h"
#include "skel_message.pb.h"
#include "test_message.pb.h"

Q_LOGGING_CATEGORY(TESTC, "test_module")

TestModule::TestModule(QObject *parent)
{
    setParent(parent);
    this->name = "test_instance";
    qCDebug(TESTC, "hello,world");
}

void TestModule::start()
{

}

void TestModule::stop()
{

}

QStringList TestModule::getPubTopics()
{
    QStringList topics;
    topics << "hello1";
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
}

void TestModule::sendTestMessage()
{
    //publish("");
}

void TestModule::subscribeTopic(QString topic)
{
    qCDebug(TESTC) << "test module subscribe: " << topic;
    subscribe(topic);
}
