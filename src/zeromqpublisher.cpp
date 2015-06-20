#include "zeromqpublisher.h"
#include <QDebug>
#include <QList>


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
    QList<QByteArray> toSend;

    toSend.append(QString("").toLocal8Bit());
    toSend.append(msg.toLocal8Bit());

    publisher->sendMessage(toSend);
    emit messageSend(toSend);
}
void ZeroMQPublisher::sendMessage(nzmqt::ZMQMessage *message)
{
    QList<QByteArray> toSend;

    toSend.append(QString("").toLocal8Bit());
    toSend.append(message->toByteArray());

    publisher->sendMessage(toSend);
    emit messageSend(toSend);
}
void ZeroMQPublisher::sendMessage(nzmqt::ZMQMessage *message, const QString filter)
{
    //publisher->setOption(nzmqt::ZMQSocket::OPT_SUBSCRIBE,filter.toStdString().c_str());
    QList<QByteArray> toSend;

    toSend.append(filter.toLocal8Bit());
    toSend.append(message->toByteArray());

    publisher->sendMessage(toSend);
    emit messageSend(toSend);
}
void ZeroMQPublisher::sendMessage(const QByteArray message, const QString filter)
{
    //publisher->setOption(nzmqt::ZMQSocket::OPT_SUBSCRIBE,filter.toStdString().c_str());
    QList<QByteArray> toSend;

    toSend.append(filter.toLocal8Bit());
    toSend.append(message);

    publisher->sendMessage(toSend);
    emit messageSend(toSend);
}

void ZeroMQPublisher::messageSended(const QList<QByteArray> sended)
{
    qDebug()<<"Sended: "<< sended.at(0) << " " << sended.at(1);
}

QString ZeroMQPublisher::getAddress() const
{
    return address;
}



