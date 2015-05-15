#include "zeromqsubscriber.h"
#include "context.h"

ZeroMQSubscriber::ZeroMQSubscriber()
{
   subscriber = Context::instance()->context->createSocket(nzmqt::ZMQSocket::TYP_SUB,this);
   subscriber->setLinger(0);
   connect(subscriber,SIGNAL(messageReceived(const QList<QByteArray>&)),this,SLOT(messageRecieved(const QList<QByteArray>&)));
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

