#include "zeromqpublisher.h"
#include <QDebug>


nzmqt::ZMQSocket *ZeroMQPublisher::getPublisher() const
{
    return publisher;
}

ZeroMQPublisher::ZeroMQPublisher(nzmqt::ZMQContext* context,const QString address)
{
    this->address = address;
    publisher = context->createSocket(nzmqt::ZMQSocket::TYP_PUB);
    publisher->connectTo(address);
    connect(this,SIGNAL(messageSend(QByteArray)),this,SLOT(messageSended(QByteArray)));
}

void ZeroMQPublisher::close()
{
    publisher->close();
}

void ZeroMQPublisher::sendMessage(const QString msg)
{
    publisher->sendMessage(msg.toLocal8Bit());
    emit messageSend(msg.toLocal8Bit());
}
void ZeroMQPublisher::sendMessage(nzmqt::ZMQMessage* msg)
{
   // QByteArray array = msg.toByteArray();
    publisher->sendMessage(msg->toByteArray());
    emit messageSend(msg->toByteArray());
}

void ZeroMQPublisher::messageSended(const QByteArray sended)
{
    qDebug()<<"Sended: "<<sended;
}

QString ZeroMQPublisher::getAddress() const
{
    return address;
}



