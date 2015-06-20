#include "skel.h"

#include <test_message.pb.h>
#include <skel_message.pb.h>
#include <skel_message2.pb.h>

Q_LOGGING_CATEGORY(SKELETON, "skel");

Skel::Skel(QObject *parent)
{
    setParent(parent);

    this->name = "skel works";
    ::indigo::pb::test_message test2;

	::indigo::pb::skel_message skel;
	::indigo::pb::skel_message2 skel2;

    qCDebug(SKELETON, "hello,world");
}

Skel::~Skel()
{

}

QStringList Skel::getPubTopics()
{
    QStringList topics;
    topics << "skel_topic";

    return topics;
}

void Skel::respond(QString topic, indigo::pb::internal_msg &message)
{
    if (message.HasExtension(::indigo::pb::skel_message::skel_message_in)) {
        qCWarning(SKELETON, "got my message!");
    }

    if (message.HasExtension(::indigo::pb::skel_message2::skel_message_2_in)) {
        qCWarning(SKELETON, "got my message2!");
    }

    if (message.HasExtension(::indigo::pb::test_message::test_message_in)) {
        qCWarning(SKELETON, "WTF!");
    }
}

void Skel::start()
{
    ::indigo::pb::internal_msg msg;
    ::indigo::pb::skel_message *my_msg = msg.MutableExtension(::indigo::pb::skel_message::skel_message_in);

    static int counter = 0;
    my_msg->set_data(counter++);

    publish(msg, "skel");
}

void Skel::stop()
{

}
