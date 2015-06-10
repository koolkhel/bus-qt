#include "skel.h"

#include <test_message.pb.h>
#include <skel_message.pb.h>
#include <skel_message2.pb.h>

Q_LOGGING_CATEGORY(SKELETON, "skel");

Skel::Skel(QObject *parent)
{
    //this->name = "skel works";
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

void Skel::respond(indigo::pb::internal_msg &message)
{
    if (message.HasExtension(::indigo::pb::skel_message::skel_message_in)) {
        qCWarning(SKELETON, "got my message!");
    }

    if (message.HasExtension(::indigo::pb::skel_message2::skel_message_2_in)) {
        qCWarning(SKELETON, "got my message2!");
    }
}

void Skel::start()
{

}

void Skel::stop()
{

}
