#include "modulep.h"
#include <QString>
#include <QDebug>


ModuleP::ModuleP(QString& string)
{
    debugInfo = string;
}

QString ModuleP::getDebugInfo() const
{
    return debugInfo;
}

void ModuleP::setDebugInfo(const QString &value)
{
    debugInfo = value;
}

ZeroMQPublisher *ModuleP::getPublisher() const
{
    return publisher;
}

void ModuleP::setPublisher(ZeroMQPublisher *value)
{
    publisher = value;
    publisher->getPublisher()->setLinger(5);
}

ZeroMQSubscriber *ModuleP::getSubscriber() const
{
    return subscriber;
}

void ModuleP::setSubscriber(ZeroMQSubscriber *value)
{
    subscriber = value;
    connect(subscriber, SIGNAL(message(const QList<QByteArray> &)), SIGNAL(messageReceived(const QList<QByteArray>&)));
    subscriber->getSubscriber()->setLinger(5);
}

void ModuleP::printDebug()
{
    qDebug()<<debugInfo;
}


