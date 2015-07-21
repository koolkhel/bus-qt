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

            quint64 content = msg.content();
            int sz = msg.content_size();
            quint64 checker = 0ll;
            for(int i = 0; i < sz; ++i) {
                if((content  >> i) & 1) {
                    ++bounced[i];
                    if(bounced[i] > 5) {
                        checker |= (1<<i);
                    }
                } else {
                    bounced[i] = 0;
                }
            }

            if(!checker) {
                publish(message, filtredMessage); //all ok
            } else {
                publish(message, LimitTopic); //spam
            }
        }
    } else {
        memset(bounced, 0, 64);
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
