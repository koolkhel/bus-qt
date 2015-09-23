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
    qCDebug(SENDERC) << "received message on topic " << topic;
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
    //qRegisterMetaType< ::indigo::pb::indigo_msg&>();
    connect(network, SIGNAL(messageReceived(::indigo::pb::indigo_msg&)), SLOT(serverMessageReceived(::indigo::pb::indigo_msg&)));
    network->start();

    subscribe(getConfigurationParameter("sendTopic", "to_send").toString());

    senderTimer = new QTimer(this);
    senderTimer->setInterval(getConfigurationParameter("sendInterval", 5 * 1000).toInt());
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

    // do not send empty messages as of yet
    if (currentMessage->sampleIds().count() == 0)
        return;

    sentMessage = currentMessage;

    // новые данные идут уже в новый класс
    currentMessage = new OutgoingMessage(this);

    locker.unlock();

    // уходящее сообщение штампуем
    int id = outgoingMessageId++;
    sentMessage->setId(id);

    // отправляем (с потерями)
    qCDebug(SENDERC) << QString("queuing server message id %1 with %2 messages")
                        .arg(sentMessage->id())
                        .arg(sentMessage->sampleIds().count());
    network->queueMessage(sentMessage->msg());

    // ждем обратно
    sentMessageTimeoutTimer->start();
}

void SENDER::stop()
{
    senderTimer->stop();
    senderTimer->deleteLater();

    network->stop();
    network->deleteLater();

    if (sentMessage) {
        sentMessage->deleteLater();
        sentMessage = NULL;
    }

    if (currentMessage) {
        currentMessage->deleteLater();
        currentMessage = NULL;
    }
}

void SENDER::readKey()
{
    QString key = getConfigurationParameter("uuid", "none").toString();
    if (key == "none") {
        QFile keyFile(getConfigurationParameter("uuidFile", "/opt/key.txt").toString());
        if (!keyFile.open(QIODevice::ReadOnly)) {
            qFatal("couldn't open key file\n");
        }

        QTextStream in(&keyFile);
        key = in.readLine();


        if (key.size() < 8)
            qFatal("please provide uuid for sender module in /opt/key.txt");
    }

    qCDebug(SENDERC) << "using id " << key;

    key = key.remove("-");

    bool ok = false;
    u_int64_t most = key.mid(0, 16).toULongLong(&ok, 16);
    u_int64_t least = key.mid(16, 16).toULongLong(&ok, 16);

    qCDebug(SENDERC) << QString("sender uses key: %1 %2").arg(least, 0, 16).arg(most, 0, 16);

    if (ok) {
        deviceId.set_least_significant_bits(least);
        deviceId.set_most_significant_bits(most);
    } else {
        qFatal(qPrintable("could not read key"));
    }
}

void SENDER::handleServerConfirmation(indigo::pb::indigo_msg &message)
{
    ::indigo::pb::confirmed_messages serverConfirmed = message.GetExtension(
                ::indigo::pb::confirmed_messages::confirmed_messages_out);
    if (serverConfirmed.message_ids_size() != 1) {
        qCWarning(SENDERC) << "got more confirmations than it should be: " << serverConfirmed.message_ids_size();
    }

    if (serverConfirmed.message_ids(0) != sentMessage->id()) {
        qCWarning(SENDERC) << QString("got wrong confirmation: %1 but expected %2")
                              .arg(serverConfirmed.message_ids(0))
                              .arg(sentMessage->id());
        return;
    }

    // готовимся публиковать ответ
    ::indigo::pb::internal_msg msg;

    ::indigo::pb::confirmed_messages blackboxConfirmed = msg.GetExtension(
                ::indigo::pb::confirmed_messages::confirmed_messages_in);

    // по всем подтвержденным идшникам
    qCDebug(SENDERC) << "confirming server message " << sentMessage->id() << " with " << sentMessage->sampleIds().count() << " samples";


    foreach (int sampleId, sentMessage->sampleIds())  {
        blackboxConfirmed.add_message_ids(sampleId);
    }

    // пусть черный ящик успокоится
    publish(msg, "confirmed_messages");

    sentMessageTimeoutTimer->stop();
    sentMessage->deleteLater();
    sentMessage = NULL;
}

void SENDER::serverMessageReceived(::indigo::pb::indigo_msg &message)
{
    // пришли подтверждения с сервера
    if (message.HasExtension(::indigo::pb::confirmed_messages::confirmed_messages_out)) {
        if (sentMessage == NULL) {
            qCWarning(SENDERC) << "confirmation received, but no messages sent yet";
        }

        handleServerConfirmation(message);
    } // confirmation handling

}

void SENDER::sentMessageTimeout()
{
    qCWarning(SENDERC) << "send message timeout, retrying id " << sentMessage->id();

    // отправляем (с потерями)
    network->queueMessage(sentMessage->msg());

    // ждем обратно
    sentMessageTimeoutTimer->start();
}
