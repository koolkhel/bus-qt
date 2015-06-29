#include "blackbox.h"

Q_LOGGING_CATEGORY(BLACKBOXC, "blackbox")

BLACKBOX::BLACKBOX(QObject *parent)
{
    setParent(parent);

    this->name = "blackbox works";

    qCDebug(BLACKBOXC, "hello,world");
}

BLACKBOX::~BLACKBOX()
{

}

QStringList BLACKBOX::getPubTopics()
{
    QStringList topics;

    return topics;
}

void BLACKBOX::respond(QString topic, indigo::pb::internal_msg &message)
{
}

void BLACKBOX::start()
{
}

void BLACKBOX::stop()
{
}
