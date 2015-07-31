#include "debounce.h"

#include "indigo_message.pb.h"

Q_LOGGING_CATEGORY(DEBOUNCEC, "debounce")

DEBOUNCE::DEBOUNCE(QObject *parent)
    :
      LimitTopic("spam")
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

    topics << LimitTopic << filtredTopic;

    return topics;
}

void DEBOUNCE::respond(QString topic, indigo::pb::internal_msg &message)
{
    if(topic.compare(LimitTopic) == 0 || topic.compare(filtredTopic) == 0) {
        return;
    }
    if (message.HasExtension(::indigo::pb::io_message::io_message_in)) {
        ::indigo::pb::io_message msg = message.GetExtension(::indigo::pb::io_message::io_message_in);
        if(msg.io_id() == id) {
            quint32 content = msg.content();
            if(timer.elapsed() <= timeout && content) {
                ++bounceCounter;
                if(bounceCounter <= limitBounce) {
                    publish(message, filtredTopic);
                } else {
                    publish(message, LimitTopic);
                }
            }
        }
    }
    timer = QTime::currentTime();
}


void DEBOUNCE::start()
{
    QString inputTopic = getConfigurationParameter("inputTopic", "io_in").toString();
    limitBounce        = getConfigurationParameter("limitBounce", 5).toInt();
    timeout            = getConfigurationParameter("timeout", 200).toInt();
    id                 = static_cast< ::indigo::pb::io_message_IO_id > (getConfigurationParameter("id", 0).toInt());

    if(id == ::indigo::pb::io_message_IO_id_DEFAULT) {
        qCWarning(DEBOUNCEC) << "default id";
    }

    subscribe(inputTopic);

}

void DEBOUNCE::stop()
{
}
