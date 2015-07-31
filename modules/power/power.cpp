#include "power.h"
#include "io_message.pb.h"

Q_LOGGING_CATEGORY(POWERC, "power")

POWER::POWER(QObject *parent)
{
    setParent(parent);

    this->name = "power works";

    delayedStart = 100;

    connect(&timer, SIGNAL(timeout()), this, SLOT(doPowerJob()));

    errorTopic = "power issue";

    qCDebug(POWERC, "hello,world");
}

POWER::~POWER()
{

}

QStringList POWER::getPubTopics()
{
    QStringList topics;

    topics << errorTopic;

    return topics;
}

void POWER::respond(QString topic, indigo::pb::internal_msg &message)
{
    if(message.HasExtension(indigo::pb::io_message::io_message_in)) {
        indigo::pb::io_message msg = message.GetExtension(indigo::pb::io_message::io_message_in);
        if(privateId.find(msg.io_id()) != privateId.end()) {
            qCDebug(POWERC) << "Recived data" << msg.content();
            devices[msg.io_id()] = msg.content();
        }
    }
}

void POWER::doPowerJob()
{
    if(delayedStart > 0) {
        --delayedStart;
        return;
    }
    int value = 1;
    for(QMap<int, int>::const_iterator it = devices.cbegin(); it != devices.cend(); ++it) {
        value &= static_cast < bool > (it.value());
    }
    if(!value) {
        ::indigo::pb::internal_msg message;
        publish(message, errorTopic);
    }
}

void POWER::start()
{
    delayedStart = getConfigurationParameter("delayedStart", 1).toInt();
    int interval = getConfigurationParameter("interval", 200).toInt();

    QStringList devices = getConfigurationParameter("devices", "").toStringList();

    if(devices.size() != 10) {
        qCWarning(POWERC) << "Not 10 devices in config" << getConfigurationParameter("devices", "");
    }

    foreach (QString topic, devices) {
        privateId.insert(topic.toInt());
    }

    subscribe("io_in");
    timer.setSingleShot(false);

    timer.start(interval);
}

void POWER::stop()
{
    timer.stop();
}
