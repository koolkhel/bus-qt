#include "power.h"
#include "io_message.pb.h"
#include "power_message.pb.h"

Q_LOGGING_CATEGORY(POWERC, "power")

POWER::POWER(QObject *parent)
{
    setParent(parent);

    this->name = "power works";

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
        if(privateID.keys().indexOf(msg.io_id()) != -1) {
            privateID[msg.io_id()] = msg.value();
            doPowerJob();
        }
    }
}



void POWER::doPowerJob()
{
    indigo::pb::power_message::STAT       STAT1;
    indigo::pb::power_message::STAT       STAT2;
    indigo::pb::power_message::ACpg_STATE acpg;
    if(privateID[ACPG] == 1) {
        acpg = indigo::pb::power_message_ACpg_STATE_GOOD;
    } else {
        acpg = indigo::pb::power_message_ACpg_STATE_BAD;
    }

    if(privateID[S1] == 1 && privateID[S2] == 1) {
        STAT1 = indigo::pb::power_message_STAT_PCH_PROG;
    } else if (privateID[S1] == 1 && privateID[S2] == 0) {
        STAT1 = indigo::pb::power_message_STAT_FCH_PROG;
    } else if (privateID[S1] == 0 && privateID[S2] == 1) {
        STAT1 = indigo::pb::power_message_STAT_CH_DONE;
    } else if (privateID[S1] == 0 && privateID[S2] == 0) {
        STAT1 = indigo::pb::power_message_STAT_CH_SUSP;
    } else {
        qCWarning(POWERC) << "HOW?";
    }

    indigo::pb::internal_msg pwrMessage;
    indigo::pb::power_message *pwr = pwrMessage.MutableExtension(indigo::pb::power_message::power_message_in);
    pwr->set_acpg(acpg);
    pwr->set_stat1(STAT1);

    publish(pwrMessage, powerTopic);
}

void POWER::start()
{

    powerTopic = getConfigurationParameter("powerTopic", "power").toString();
    S1 = getConfigurationParameter("S1_ID", -1).toInt();
    privateID[S1] = 0;
    if(S1 == -1) {
        qCWarning(POWERC) << "S1 wrong id";
    }

    S2 = getConfigurationParameter("S2_ID", -1).toInt();
    privateID[S2] = 0;
    if(S2 == -1) {
        qCWarning(POWERC) << "S2 wrong id";
    }

    ACPG = getConfigurationParameter("ACPG_ID", -1).toInt();
    privateID[ACPG] = 1;
    if(ACPG == -1) {
        qCWarning(POWERC) << "ACPG wrong id";
    }

    QString inputTopic = getConfigurationParameter("inputTopic", "io_in").toString();
    subscribe(inputTopic);
}

void POWER::stop()
{
    privateID.clear();
}
