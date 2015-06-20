#include "zeromqpublisher.h"
#include <QDebug>
#include <QList>


nzmqt::ZMQSocket *ZeroMQPublisher::getPublisher() const
{
    return publisher;
}

ZeroMQPublisher::ZeroMQPublisher(nzmqt::ZMQContext* context,const QString bindAddress)
{
    this->address = bindAddress;
    publisher = context->createSocket(nzmqt::ZMQSocket::TYP_PUB);
    publisher->bindTo(bindAddress);
    assert(publisher != NULL);

    connect(this, SIGNAL(messageSend(QList<QByteArray>)),
            this, SLOT(messageSended(QList<QByteArray>)));
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

    assert(publisher != NULL);
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



