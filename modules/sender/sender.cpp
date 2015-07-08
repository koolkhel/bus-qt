#include "sender.h"

#include <QFile>
#include <QTimer>
#include <QMutexLocker>

#include "protobufnegotiator.h"

#include "gpsmodule_message.pb.h"
#include "geo_message.pb.h"
#include "blackbox_message.pb.h"

#include "outgoingmessage.h"

Q_LOGGING_CATEGORY(SENDERC, "sender")


SENDER::SENDER(QObject *parent)
{
    setParent(parent);

    this->name = "sender works";

    qCDebug(SENDERC, "hello,world");

    outgoingMessageId = 0;

    currentMessage = NULL;
    sentMessage = NULL;
}

SENDER::~SENDER()
{

}

QStringList SENDER::getPubTopics()
{
    QStringList topics;

    return topics;
}

void SENDER::respond(QString topic, indigo::pb::internal_msg &message)
{
    if (topic != getConfigurationParameter("sendTopic", "tosend").toString())
        return;

    QMutexLocker locker(&outgoingMessageMutex);
    currentMessage->consumeSample(topic, message);
}

void SENDER::start()
{
    qCDebug(SENDERC) << "starting sender";
    readKey();

    currentMessage = new OutgoingMessage(this);

    network = new ProtobufNegotiator(
                getConfigurationParameter("serverAddress", "serv.indigosystem.ru").toString(),
                getConfigurationParameter("serverPort", 9909).toInt(),
                deviceId,
                this);

    network->start();

    subscribe(getConfigurationParameter("sendTopic", "tosend").toString());

    senderTimer = new QTimer(this);
    senderTimer->setInterval(getConfigurationParameter("sendInterval", 5000).toInt());
    senderTimer->setSingleShot(false);
    connect(senderTimer, SIGNAL(timeout()), SLOT(performSend()));
    senderTimer->start();

    sentMessageTimeoutTimer = new QTimer(this);
    sentMessageTimeoutTimer->setInterval(getConfigurationParameter("sendTimeout", 80 * 1000).toInt());
    sentMessageTimeoutTimer->setSingleShot(true);
    connect(sentMessageTimeoutTimer, SIGNAL(timeout()), SLOT(sentMessageTimeout()));
}

void SENDER::performSend()
{
    qCDebug(SENDERC) << "send cycle starts";
    QMutexLocker locker(&outgoingMessageMutex);

    // еще не отправилось, а мы следующее шлем
    if (sentMessage != NULL)
        return;

    // уходящее сообщение штампуем
    int id = outgoingMessageId++;
    currentMessage->setId(id);

    // отправляем (с потерями)
    qCDebug(SENDERC) << "queuing message server id " << id;
    network->queueMessage(currentMessage->msg());

    // ждем обратно
    sentMessageTimeoutTimer->start();
    sentMessage = currentMessage;

    // новые данные идут уже в новый класс
    currentMessage = new OutgoingMessage(this);
}

void SENDER::stop()
{
    senderTimer->stop();
    senderTimer->deleteLater();

    network->stop();
    network->deleteLater();
}

void SENDER::readKey()
{
    QString key = getConfigurationParameter("uuid", "none").toString();
    if (key == "none") {
        qFatal("please provide uuid for sender module");
    }

    qCDebug(SENDERC) << "using id " << key;

    key = key.remove("-");

    bool ok = false;
    u_int64_t least = key.mid(0, 16).toULongLong(&ok, 16);
    u_int64_t most = key.mid(16, 16).toULongLong(&ok, 16);

    qCDebug(SENDERC) << QString("%1 %2").arg(least, 0, 16).arg(most, 0, 16);

    if (ok) {
        deviceId.set_least_significant_bits(least);
        deviceId.set_most_significant_bits(most);
    } else {
        qFatal(qPrintable("could not read key"));
    }
}

 void SENDER::serverMessageReceived(::indigo::pb::indigo_msg &message)
 {
     // пришли подтверждения с сервера
     if (message.HasExtension(::indigo::pb::confirmed_messages::confirmed_messages_out)) {
         if (sentMessage == NULL) {
             qCWarning(SENDERC) << "confirmation received, but no messages sent yet";
         }

         // готовимся публиковать ответ
         ::indigo::pb::internal_msg msg;

        ::indigo::pb::confirmed_messages serverConfirmed = msg.GetExtension(
                     ::indigo::pb::confirmed_messages::confirmed_messages_in);

         // по всем подтвержденным идшникам
         if (serverConfirmed.message_ids_size() != 1)
             qCWarning(SENDERC) << "got more confirmations than it should be";

         for (int i = 0; i < serverConfirmed.message_ids_size(); i++) {
             int confirmedId = serverConfirmed.message_ids(i);

             // нашли подтверждение конкретно того, что отправляли
             if (confirmedId == sentMessage->id()) {
                 qCDebug(SENDERC) << "confirming server message " << confirmedId;
                 foreach (int sampleId, sentMessage->sampleIds())  {
                    serverConfirmed.add_message_ids(sampleId);
                 }

                 // пусть черный ящик успокоится
                 publish(msg, "confirmed_messages");

                 sentMessageTimeoutTimer->stop();
                 sentMessage->deleteLater();
                 sentMessage = NULL;
             }
         }
     }

     if (message.HasExtension(::indigo::pb::indigo_geo::geo_coords)) {

    }
 }

 void SENDER::sentMessageTimeout()
 {
     qCWarning(SENDERC) << "send message timeout, retrying";

     // отправляем (с потерями)
     network->queueMessage(sentMessage->msg());

     // ждем обратно
     sentMessageTimeoutTimer->start();
 }
