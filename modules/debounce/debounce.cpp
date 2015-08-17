#include "debounce.h"

#include "indigo_message.pb.h"

Q_LOGGING_CATEGORY(DEBOUNCEC, "debounce")

DEBOUNCE::DEBOUNCE(QObject *parent)
    :
      limitTopic("spam")
{
    setParent(parent);

    this->name = "debounce works";

    connect(&bounceStarted, SIGNAL(timeout()), this, SLOT(stabilized()));

    qCDebug(DEBOUNCEC, "initialized");
}

DEBOUNCE::~DEBOUNCE()
{
}

QStringList DEBOUNCE::getPubTopics()
{
    QStringList topics;

    topics << limitTopic << filtredTopic << bounceStartedTopic;

    return topics;
}

void DEBOUNCE::respond(QString topic, indigo::pb::internal_msg &message)
{
    if(inputCheck(topic, message)) {
        ::indigo::pb::io_message *msg = message.MutableExtension(::indigo::pb::io_message::io_message_in);
        if(msg->io_id() == id) {
            bounceStarted.start();
            dbcMessage = message;
            switch(state) {
            default:
                qCWarning(DEBOUNCEC) << "Wrong state"; break;
            case 0:
                state = 1;
                msg->set_state(::indigo::pb::io_message_debounce_state_DEBOUNCE);
                epoch = (QTime::currentTime().msecsSinceStartOfDay()); break;
            case 1:
                state = 2;
                msg->set_epoch(epoch);
                publish(dbcMessage, bounceStartedTopic); break;
            case 2:
                if((QTime::currentTime().msecsSinceStartOfDay() - epoch) > timeout) {
                    msg->set_state(::indigo::pb::io_message_debounce_state_DEBOUNCE_LETAL);
                    publish(dbcMessage, limitTopic);
                    state = 3;
                } break;
            case 3: break;
            }
        }

    }
}

bool DEBOUNCE::inputCheck(QString topic, indigo::pb::internal_msg &message)
{
    if(topic.compare(limitTopic) == 0 || topic.compare(filtredTopic) == 0) {
        return false;
    }
    if (message.HasExtension(::indigo::pb::io_message::io_message_in)) {
       return true;
    }
    return false;
}

void DEBOUNCE::stabilized()
{
    state = 0;
    ::indigo::pb::io_message *msg = dbcMessage.MutableExtension(::indigo::pb::io_message::io_message_in);
    msg->set_state(indigo::pb::io_message_debounce_state_STABLE);
    publish(dbcMessage, filtredTopic);
}


void DEBOUNCE::start()
{
    state = 0;
    bounceStartedTopic = getConfigurationParameter("bounceStartedTopic", "bnc_str").toString();
    QString inputTopic = getConfigurationParameter("inputTopic", "io_in").toString();
    filtredTopic       = getConfigurationParameter("filtredTopic", "iof_in").toString();
    limitTopic         = getConfigurationParameter("limitTopic", "bnc_end").toString();
    timeout            = getConfigurationParameter("timeout", 200).toInt();
    id                 = static_cast< ::indigo::pb::io_message_IO_id > (getConfigurationParameter("id", 0).toInt());
    
    if(id == ::indigo::pb::io_message_IO_id_DEFAULT) {
        qCWarning(DEBOUNCEC) << "default id";
    }

    subscribe(inputTopic);

}

void DEBOUNCE::stop()
{
    bounceStarted.stop();
}
