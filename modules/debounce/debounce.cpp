#include "debounce.h"

#include "indigo_message.pb.h"

Q_LOGGING_CATEGORY(DEBOUNCEC, "debounce")

DEBOUNCE::DEBOUNCE(QObject *parent)
    :
      LimitTopic("spam")
{
    setParent(parent);

    this->name = "debounce works";
    dbc = dbcMessage.MutableExtension(indigo::pb::debounce_message::debounce_message_in);
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
    if(inputCheck(topic, message)) {
        ::indigo::pb::io_message msg = message.GetExtension(::indigo::pb::io_message::io_message_in);
        if(msg.io_id() == id) {
            bounceStarted.start();
            dbc->set_allocated_msg(&message);
            switch(state) {
              default:
                    qCWarning(DEBOUNCEC) << "Wrong state"; break;
              case 0:
                    state = 1;
                    dbc->set_state(::indigo::pb::debounce_message_debounce_state_DEBOUNCE);
                    dbc->set_epoch(QTime::currentTime().msecsSinceStartOfDay()); break;
              case 1:
                    state = 2;
                    publish(dbcMessage, "STARTED BOUNCE"); break;
               case 2: if((QTime::currentTime().msecsSinceStartOfDay() - dbc->epoch()) > timeout) {
                    dbc->set_state(::indigo::pb::debounce_message_debounce_state_DEBOUNCE_LETAL);
                    publish(dbcMessage, "FATAL BOUNCE");
                } break;
            }
        }

    }
}

bool DEBOUNCE::inputCheck(QString topic, indigo::pb::internal_msg &message)
{
    if(topic.compare(LimitTopic) == 0 || topic.compare(filtredTopic) == 0) {
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
    dbc->set_state(indigo::pb::debounce_message_debounce_state_DEBOUNCE);
    publish(dbcMessage, filtredTopic);
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
