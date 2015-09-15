#include "zeromqpublisher.h"
#include <QDebug>
#include <QList>

#include "indigo.h"

nzmqt::ZMQSocket *ZeroMQPublisher::getPublisher() const
{
    return publisher;
}

ZeroMQPublisher::ZeroMQPublisher(nzmqt::ZMQContext* context,const QString bindAddress, QObject *parent)
    : QObject(parent)
{
    _bindAddress = bindAddress;
    _context = context;
}

void ZeroMQPublisher::start()
{
    INDIGO_CHECK_THREAD;

    this->address = _bindAddress;
    publisher = _context->createSocket(nzmqt::ZMQSocket::TYP_PUB);
    publisher->bindTo(_bindAddress);
    assert(publisher != NULL);

    connect(this, SIGNAL(messageSend(QList<QByteArray>)),
            this, SLOT(messageSended(QList<QByteArray>)));
}

void ZeroMQPublisher::close()
{
    INDIGO_CHECK_THREAD;
    publisher->close();
}


void ZeroMQPublisher::connectTo(QString address)
{
    INDIGO_CHECK_THREAD;

    publisher->connectTo(address);
}

#if 0
void ZeroMQPublisher::sendMessage(const QString msg)
{
    INDIGO_CHECK_THREAD;
    QList<QByteArray> toSend;

    toSend.append(QString("").toLocal8Bit());
    toSend.append(msg.toLocal8Bit());

    publisher->sendMessage(toSend);
    emit messageSend(toSend);
}
void ZeroMQPublisher::sendMessage(nzmqt::ZMQMessage *message)
{
    INDIGO_CHECK_THREAD;
    QList<QByteArray> toSend;

    toSend.append(QString("").toLocal8Bit());
    toSend.append(message->toByteArray());

    publisher->sendMessage(toSend);
    emit messageSend(toSend);
}
void ZeroMQPublisher::sendMessage(nzmqt::ZMQMessage *message, const QString filter)
{
    INDIGO_CHECK_THREAD;
    //publisher->setOption(nzmqt::ZMQSocket::OPT_SUBSCRIBE,filter.toStdString().c_str());
    QList<QByteArray> toSend;

    toSend.append(filter.toLocal8Bit());
    toSend.append(message->toByteArray());

    publisher->sendMessage(toSend);
    emit messageSend(toSend);
}
#endif

void ZeroMQPublisher::sendMessage(const QByteArray message, const QString filter)
{
    INDIGO_CHECK_THREAD;
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
    qCDebug(ZMQ)<<"Sent: " << sended.at(0) << " bytes:" << sended.at(1).size() << " data: " << sended.at(1).toHex();
}

QString ZeroMQPublisher::getAddress() const
{
    return address;
}



