#include "zeromqpublisher.h"
#include <QDebug>


nzmqt::ZMQSocket *ZeroMQPublisher::getPublisher() const
{
    return publisher;
}
ZeroMQPublisher::ZeroMQPublisher(const QString address,nzmqt::ZMQContext* context)
{
    this->address = address;
    publisher = context->createSocket(nzmqt::ZMQSocket::TYP_PUB);
    publisher->bindTo(address);
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

void ZeroMQPublisher::messageSended(const QByteArray sended)
{
    qDebug()<<"Sended: "<<sended;
}

QString ZeroMQPublisher::getAddress() const
{
    return address;
}



