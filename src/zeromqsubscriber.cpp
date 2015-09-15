#include "zeromqsubscriber.h"
#include <QDebug>

#include "indigo.h"

ZeroMQSubscriber::ZeroMQSubscriber(nzmqt::ZMQContext* context, QObject *parent)
    : QObject(parent)
{
    _context = context;
}

void ZeroMQSubscriber::start()
{
    INDIGO_CHECK_THREAD;

    subscriber = _context->createSocket(nzmqt::ZMQSocket::TYP_SUB);

    connect(subscriber, SIGNAL(messageReceived(const QList<QByteArray>&)),
            SLOT(messageRecieved(const QList<QByteArray>&)));
    connect(subscriber, SIGNAL(messageReceived(const QList<QByteArray>&)),
            SIGNAL(message(const QList<QByteArray>&)));
}

void ZeroMQSubscriber::subscribe(QString subscriberFilter)
{
    INDIGO_CHECK_THREAD;

    subscriber->subscribeTo(subscriberFilter);
}

void ZeroMQSubscriber::connectTo(QString address)
{
    INDIGO_CHECK_THREAD;

    subscriber->connectTo(address);
}

nzmqt::ZMQSocket *ZeroMQSubscriber::getSubscriber() const
{
    return subscriber;
}

#if 0
bool ZeroMQSubscriber::recieve(nzmqt::ZMQMessage *message)
{
    qCDebug(ZMQ) << "receive not should be";
    subscriber->receiveMessage(message);
    if (message->size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
#endif

void ZeroMQSubscriber::close()
{
    subscriber->close();
}

void ZeroMQSubscriber::messageRecieved(const QList<QByteArray>& message)
{
    qCDebug(ZMQ)<<"Received: message";
}

