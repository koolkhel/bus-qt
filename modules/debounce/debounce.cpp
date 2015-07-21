#include "debounce.h"

#include "io_message.pb.h"
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

    topics << LimitTopic << id;

    return topics;
}

void DEBOUNCE::respond(QString topic, indigo::pb::internal_msg &message)
{
    qDebug() << "topic" << topic;
    if(topic.compare(LimitTopic) == 0 || topic.compare(id) == 0) {
        return;
    }
    if (message.HasExtension(::indigo::pb::io_message::io_message_in)) {
        ::indigo::pb::io_message msg = message.GetExtension(::indigo::pb::io_message::io_message_in);
        quint32 content = msg.content();
        if(timer.elapsed() <= 200 && content) {
            ++bounceCounter;
            if(bounceCounter <= 5) {
                publish(msg, id);
            } else {
                publish(msg, LimitTopic);
            }
        }
    }
    timer = QTime::currentTime();
}


void DEBOUNCE::start()
{
    QString device = getConfigurationParameter("id", "").toString();
    id = "iof" + device;

    subscribe("io" + device);

}

void DEBOUNCE::stop()
{
}
