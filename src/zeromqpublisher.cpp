#include "zeromqpublisher.h"
#include <QDebug>
#include "context.h"

ZeroMQPublisher::ZeroMQPublisher(const QString address, const QString filter)
{
    this->address = address;
    this->filter = filter;
    publisher = Context::instance()->context->createSocket(nzmqt::ZMQSocket::TYP_PUB,this);
    publisher->connectTo(address);
    //publisher->bindTo(address);
    connect(this,SIGNAL(messageSend(QByteArray)),this,SLOT(messageSended(QByteArray)));
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

QString ZeroMQPublisher::getFilter() const
{
    return filter;
}

void ZeroMQPublisher::setFilter(const QString &value)
{
    filter = value;
}

QString ZeroMQPublisher::getAddress() const
{
    return address;
}

void ZeroMQPublisher::setAddress(const QString &value)
{
    address = value;
}

