#include "zeromqsubscriber.h"
#include "context.h"

ZeroMQSubscriber::ZeroMQSubscriber(nzmqt::ZMQContext* context)
{
   subscriber = context->createSocket(nzmqt::ZMQSocket::TYP_SUB);

   connect(subscriber, SIGNAL(messageReceived(const QList<QByteArray>&)), SIGNAL(recieved()));
   connect(subscriber, SIGNAL(messageReceived(const QList<QByteArray>&)), SLOT(messageRecieved(const QList<QByteArray>&)));
}

void ZeroMQSubscriber::subscribeTo(QString address,QString subscriberFilter)
{
    subscriber->connectTo(address);
    subscriber->subscribeTo(subscriberFilter);
}

void ZeroMQSubscriber::close()
{
    subscriber->close();
}

void ZeroMQSubscriber::messageRecieved(const QList<QByteArray>& message)
{
    qDebug()<<"Recieved: "<<message;
}

