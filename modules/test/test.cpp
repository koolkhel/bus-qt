#include "test.h"

#include "skel_message.pb.h"

#include "test_message.pb.h"

Q_LOGGING_CATEGORY(TESTC, "test_module");

TestModule::TestModule(QObject *parent)
{
    ::indigo::pb::test_message test;

    ::indigo::pb::skel_message skel;

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

QString TestModule::getName() const
{
    // FIXME заполнять поле "имя" согласно инишнику
    return "test_instance";
}

void TestModule::respond(::indigo::pb::internal_msg &message)
{
    // TODO
}
