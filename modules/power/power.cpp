#include "power.h"
#include "io_message.pb.h"
#include "power_message.pb.h"
#include <QDateTime>
Q_LOGGING_CATEGORY(POWERC, "power")

using namespace indigo::pb;

POWER::POWER(QObject *parent)
{
    setParent(parent);

    this->name = "power works";

    qCDebug(POWERC, "hello,world");
}

POWER::~POWER()
{

}

QStringList POWER::getPubTopics()
{
    QStringList topics;

    topics << powerTopic;

    return topics;
}

void POWER::respond(QString topic, internal_msg &message)
{
    if(message.HasExtension(io_message::io_message_in)) {
        io_message msg = message.GetExtension(io_message::io_message_in);
        if(privateID.keys().indexOf(msg.io_id()) != -1) {
            qCDebug(POWERC) << "[id]=" << msg.io_id() <<"[old]=" << privateID[msg.io_id()] << "[new]="<< msg.value();
            if(msg.bounce() == io_message_bounce_state_BOUNCE) {
                privateID[msg.io_id()] = -1;
            } else {
                privateID[msg.io_id()] = msg.value();
            }
            doPowerJob();
        }
    }
}



void POWER::doPowerJob()
{
    power_message::ChargerStatus STAT;
    power_message::PowerStatus   acpg;
    switch(privateID[ACPG]) {
    case 0:
        acpg = power_message::RUNNING_ON_BATTERY; break;
    case 1:
        acpg = power_message::RUNNING_ON_AC;            break;
    case -1:
        acpg = power_message::POWER_UNKNOWN;         break;
    default:
        qCWarning(POWERC) << "Strange Value";                break;
    }

    if(privateID[S1] == 1 && privateID[S2] != -1) {
        STAT = power_message::BATTERY_CHARGING_IN_PROGRESS;
    } else if (privateID[S1] == 0 && privateID[S2] == 1) {
        STAT = power_message::BATTERY_CHARGED;
    } else if (privateID[S1] == 0 && privateID[S2] == 0) {
        STAT = power_message::BATTERY_NOT_CHARGING;
    } else {
        STAT = power_message::BATTERY_UNKNOWN;
    }

    indigo::pb::internal_msg pwrMessage;
    indigo::pb::power_message *pwr = pwrMessage.MutableExtension(indigo::pb::power_message::power_message_in);
    pwr->set_powerstatus(acpg);
    pwr->set_chargerstatus(STAT);
    pwr->mutable_time()->set_time(QDateTime::currentMSecsSinceEpoch() / 1000);
    publish(pwrMessage, powerTopic);
}

void POWER::start()
{
    powerTopic = getConfigurationParameter("powerTopic", "power").toString();
    S1 = getConfigurationParameter("S1_ID", -1).toInt();
    privateID[S1] = -1;
    if(S1 == -1) {
        qCWarning(POWERC) << "S1 wrong id";
    }

    S2 = getConfigurationParameter("S2_ID", -1).toInt();
    privateID[S2] = -1;
    if(S2 == -1) {
        qCWarning(POWERC) << "S2 wrong id";
    }

    ACPG = getConfigurationParameter("ACPG_ID", -1).toInt();
    privateID[ACPG] = -1;
    if(ACPG == -1) {
        qCWarning(POWERC) << "ACPG wrong id";
    }

    QStringList inputTopics = getConfigurationParameter("inputTopics", "io_in").toStringList();
    foreach(QString topic, inputTopics) {
        subscribe(topic);
    }
}

void POWER::stop()
{
    privateID.clear();
}
