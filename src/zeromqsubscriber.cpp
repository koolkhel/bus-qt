#include "zeromqsubscriber.h"
#include "context.h"

ZeroMQSubscriber::ZeroMQSubscriber()
{
   subscriber = Context::instance()->context->createSocket(nzmqt::ZMQSocket::TYP_SUB,this);

   connect(subscriber,SIGNAL(messageReceived(const QList<QByteArray>&)),this,SLOT(messageRecieved(const QList<QByteArray>&)));
}

void ZeroMQSubscriber::subscribeTo(QString address,QString subscriberFilter)
{
    subscriber->connectTo(address);
    subscriber->subscribeTo(subscriberFilter);
    subscriber->setOption(nzmqt::ZMQSocket::OPT_SUBSCRIBE, subscriberFilter.toStdString().c_str());
}

void ZeroMQSubscriber::messageRecieved(const QList<QByteArray>& message)
{
    qDebug()<<"Recieved: "<<message;
}

