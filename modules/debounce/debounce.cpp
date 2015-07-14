#include "debounce.h"

Q_LOGGING_CATEGORY(DEBOUNCEC, "debounce")

DEBOUNCE::DEBOUNCE(QObject *parent) : LimitTopic("spam")
{
    setParent(parent);

    this->name = "debounce works";

    setTimeout();

    qCDebug(DEBOUNCEC, "initialized");
}

DEBOUNCE::~DEBOUNCE()
{
}

QStringList DEBOUNCE::getPubTopics()
{
    QStringList topics;

    topics << LimitTopic;

    return topics;
}

void DEBOUNCE::respond(QString topic, indigo::pb::internal_msg &message)
{
    if(topic.compare(LimitTopic) == 0) {
        return;
    }

    Item temp(QTime::currentTime(), topic);
    for(int i = 0; i != items.size(); ++i) {
        if(items.at(i).first.secsTo(temp.first) > m_timeout) {
            items.removeAt(i--);
        } else {
            if(items.at(i).second ==  topic) {
                items.removeAt(i--);
                ::indigo::pb::internal_msg msg;
                publish(msg, LimitTopic);
            }
        }
    }
    items.append(temp);
}

void DEBOUNCE::setTimeout(qint64 timeout)
{
    m_timeout = timeout;
}

void DEBOUNCE::start()
{
}

void DEBOUNCE::stop()
{
}
