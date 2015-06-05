#include "test.h"

#include "skel_message.pb.h"

#include "test_message.pb.h"

Q_LOGGING_CATEGORY(TESTC, "test");

Test::Test(QObject *parent)
{
    ::indigo::pb::test_message test;

    ::indigo::pb::skel_message skel;
	qCDebug(TESTC, "hello,world");
}
