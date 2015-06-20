#include "zeromqsubscriber.h"
#include "context.h"
#include <QDebug>

ZeroMQSubscriber::ZeroMQSubscriber(nzmqt::ZMQContext* context)
{
   subscriber = context->createSocket(nzmqt::ZMQSocket::TYP_SUB);

   connect(subscriber, SIGNAL(messageReceived(const QList<QByteArray>&)),
           SLOT(messageRecieved(const QList<QByteArray>&)));
   connect(subscriber, SIGNAL(messageReceived(const QList<QByteArray>&)), SIGNAL(message(const QList<QByteArray>&)));
}

void ZeroMQSubscriber::subscribeTo(QString address,QString subscriberFilter)
{
    subscriber->connectTo(address);
    subscriber->subscribeTo(subscriberFilter);
}

nzmqt::ZMQSocket *ZeroMQSubscriber::getSubscriber() const
{
    return subscriber;
}

bool ZeroMQSubscriber::recieve(nzmqt::ZMQMessage *message)
{
    qCDebug(ZMQ) << "receive";
    subscriber->receiveMessage(message);
    if (message->size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ZeroMQSubscriber::close()
{
    subscriber->close();
}

void ZeroMQSubscriber::messageRecieved(const QList<QByteArray>& message)
{
    qCDebug(ZMQ)<<"Received: message";
}

