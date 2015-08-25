#include "debounce.h"

Q_LOGGING_CATEGORY(DEBOUNCEC, "debounce")

DEBOUNCE::DEBOUNCE(QObject *parent)
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

    topics << bounceTopic << filtredTopic;

    return topics;
}

void DEBOUNCE::respond(QString topic, indigo::pb::internal_msg &message)
{

    if(message.HasExtension(::indigo::pb::io_message::io_message_in) &&
        moduleLogic(message.GetExtension(::indigo::pb::io_message::io_message_in))) {
            dbcMessage = message;
    }
}

bool DEBOUNCE::moduleLogic(const indigo::pb::io_message &msg)
{

    if(msg.io_id() == id) {
        bounceStarted.start();
        if(state == 0) {
            epoch = msg.time();
            state = 1;
        } else if(state == 1 && ((msg.time().time() - epoch.time()) > timeout)) {
            dbcMessage.MutableExtension(::indigo::pb::io_message::io_message_in)
                    ->set_bounce(::indigo::pb::io_message_bounce_state_BOUNCE);
            publish(dbcMessage, bounceTopic);
            state = 2;
        }
        return true;
    }
    return false;
}

void DEBOUNCE::stabilized()
{
    state = 0;
    ::indigo::pb::io_message *msg = dbcMessage.MutableExtension(::indigo::pb::io_message::io_message_in);
    msg->set_bounce(indigo::pb::io_message_bounce_state_STABLE);
    publish(dbcMessage, filtredTopic);
}


void DEBOUNCE::start()
{
    state = 0;
    QString inputTopic = getConfigurationParameter("inputTopic", "io_in").toString();
    bounceTopic              = getConfigurationParameter("bounceTopic", "bnc_str").toString();
    filtredTopic                 = getConfigurationParameter("filtredTopic", "iof_in").toString();
    timeout                       = getConfigurationParameter("timeout", 200).toInt();
    int stableTime          = getConfigurationParameter("stableTime", 500).toInt();
    id                                     = static_cast< ::indigo::pb::io_message_IO_id > (getConfigurationParameter("id", 0).toInt());
    
    if(id == ::indigo::pb::io_message_IO_id_DEFAULT) {
        qCWarning(DEBOUNCEC) << "default id";
    }

    bounceStarted.setInterval(stableTime);
    bounceStarted.setSingleShot(true);

    subscribe(inputTopic);

}

void DEBOUNCE::stop()
{
    bounceStarted.stop();
}
