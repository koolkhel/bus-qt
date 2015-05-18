#include "zeromqsubscriber.h"
#include "context.h"

ZeroMQSubscriber::ZeroMQSubscriber()
{
   subscriber = Context::instance()->context->createSocket(nzmqt::ZMQSocket::TYP_SUB);
   //connect(subscriber,SIGNAL(messageReceived(QList<QByteArray>)),this,SIGNAL(recieved()));
   connect(subscriber,SIGNAL(messageReceived(QList<QByteArray>)),SIGNAL(recieved()));
   connect(subscriber,SIGNAL(messageReceived(QList<QByteArray>&)),this,SLOT(messageRecieved(QList<QByteArray>&)));
}

void ZeroMQSubscriber::subscribeTo(QString address,QString subscriberFilter)
{
    subscriber->connectTo(address);
    subscriber->subscribeTo(subscriberFilter);
}

void ZeroMQSubscriber::messageRecieved(const QList<QByteArray>& message)
{
    qDebug()<<"Recieved: "<<message;
}

