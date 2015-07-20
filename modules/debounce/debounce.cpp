#include "debounce.h"

#include "io_message.pb.h"
#include "indigo_message.pb.h"

Q_LOGGING_CATEGORY(DEBOUNCEC, "debounce")

DEBOUNCE::DEBOUNCE(QObject *parent)
    :
      LimitTopic("spam"),
      filtredMessage("iof")
{
    setParent(parent);

    this->name = "debounce works";

    qCDebug(DEBOUNCEC, "initialized");
}

DEBOUNCE::~DEBOUNCE()
{
}

QStringList DEBOUNCE::getPubTopics()
{
    QStringList topics;

    topics << LimitTopic << filtredMessage;

    return topics;
}

void DEBOUNCE::respond(QString topic, indigo::pb::internal_msg &message)
{
    qDebug() << "topic" << topic;
    if(topic.compare(LimitTopic) == 0 || topic.compare(filtredMessage) == 0) {
        return;
    }

    if(timer.elapsed() <= 200) {
        if (message.HasExtension(::indigo::pb::io_message::io_message_in)) {
            ::indigo::pb::io_message msg = message.GetExtension(::indigo::pb::io_message::io_message_in);

           qCDebug(DEBOUNCEC) << "data is: " << msg.content();
        }
    } else {
        prevState = 0;
    }
    timer = QTime::currentTime();
}


void DEBOUNCE::start()
{
    QStringList topics = getConfigurationParameter("inputTopics", "").toString().split(",");

    foreach (QString topic, topics) {
        subscribe(topic);
    }

}

void DEBOUNCE::stop()
{
}
