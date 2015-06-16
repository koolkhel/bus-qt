#include "zeromqpublisher.h"
#include <QDebug>


nzmqt::ZMQSocket *ZeroMQPublisher::getPublisher() const
{
    return publisher;
}

ZeroMQPublisher::ZeroMQPublisher(nzmqt::ZMQContext* context,const QString address)
{
    this->address = address;
    publisher = context->createSocket(nzmqt::ZMQSocket::TYP_XPUB);
    publisher->bindTo(address);
    publisher->bindTo("ipc://weather.ipc");


   // publisher->connectTo(address);
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
void ZeroMQPublisher::sendMessage(nzmqt::ZMQMessage *message)
{
    publisher->sendMessage(message->toByteArray());
    emit messageSend(message->toByteArray());
}
void ZeroMQPublisher::sendMessage(nzmqt::ZMQMessage *message, const QString filter)
{
    publisher->setOption(nzmqt::ZMQSocket::OPT_SUBSCRIBE,filter.toStdString().c_str());
    publisher->sendMessage(message->toByteArray());
    emit messageSend(message->toByteArray());
}
void ZeroMQPublisher::sendMessage(const QByteArray message, const QString filter)
{
    publisher->setOption(nzmqt::ZMQSocket::OPT_SUBSCRIBE,filter.toStdString().c_str());
    publisher->sendMessage(message);
    emit messageSend(message);

}

void ZeroMQPublisher::messageSended(const QByteArray sended)
{
    qDebug()<<"Sended: "<<sended;
}

QString ZeroMQPublisher::getAddress() const
{
    return address;
}



