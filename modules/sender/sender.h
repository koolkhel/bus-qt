#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QMutex>
#include <QVector>
#include <QAtomicInt>

#include "module.h"

#include "sender_message.pb.h"

class OutgoingMessage;

Q_DECLARE_LOGGING_CATEGORY(SENDERC)

class QTcpSocket;
class ProtobufNegotiator;
class QTimer;

class SENDER : public Module
{
	Q_OBJECT

public:
    SENDER(QObject *parent = 0);
    virtual ~SENDER();
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);

private slots:
    void serverMessageReceived(::indigo::pb::indigo_msg &message);
    void performSend();
    void sentMessageTimeout();
private:
    void handleServerConfirmation(::indigo::pb::indigo_msg &message);
    void readKey();

    ::indigo::pb::indigo_UUID deviceId;

    ProtobufNegotiator *network;

    OutgoingMessage *currentMessage;
    OutgoingMessage *sentMessage;

    QMutex outgoingMessageMutex;
    QAtomicInt outgoingMessageId;

    QTimer *senderTimer;
    QTimer *sentMessageTimeoutTimer;
};

#endif // SKEL_H
