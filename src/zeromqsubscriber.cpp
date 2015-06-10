#include "zeromqsubscriber.h"
#include "context.h"
#include <QDebug>

ZeroMQSubscriber::ZeroMQSubscriber(nzmqt::ZMQContext* context)
{
   subscriber = context->createSocket(nzmqt::ZMQSocket::TYP_XSUB);

   connect(subscriber, SIGNAL(messageReceived(const QList<QByteArray>&)), SIGNAL(recieved()));
   connect(subscriber, SIGNAL(messageReceived(const QList<QByteArray>&)), SLOT(messageRecieved(const QList<QByteArray>&)));
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

void ZeroMQSubscriber::close()
{
    subscriber->close();
}

void ZeroMQSubscriber::messageRecieved(const QList<QByteArray>& message)
{
    qDebug()<<"Recieved: "<<message;
}

