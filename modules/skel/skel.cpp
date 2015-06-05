#include "skel.h"

#include <test_message.pb.h>
#include <skel_message.pb.h>
#include <skel_message2.pb.h>

Q_LOGGING_CATEGORY(SKELETON, "skel");

Skel::Skel(QObject *parent)
{
    this->name = "skel works";
    ::indigo::pb::test_message test2;

	::indigo::pb::skel_message skel;
	::indigo::pb::skel_message2 skel2;

    qCDebug(SKELETON, "hello,world");
}

Skel::~Skel()
{

}
