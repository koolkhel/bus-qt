#include "module.h"

Q_LOGGING_CATEGORY(MODULEC, "module")

MODULE::MODULE(QObject *parent)
{
    setParent(parent);

    this->name = "module works";

    qCDebug(MODULEC, "hello,world");
}

MODULE::~MODULE()
{

}

QStringList MODULE::getPubTopics()
{
    QStringList topics;

    return topics;
}

void MODULE::respond(QString topic, indigo::pb::internal_msg &message)
{
}

void MODULE::start()
{
}

void MODULE::stop()
{
}
