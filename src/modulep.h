#ifndef MODULEP_H
#define MODULEP_H
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class ModuleP
{
    ZeroMQPublisher *publisher;
    ZeroMQSubscriber *subscriber;
    QString debugInfo;

public:

    ModuleP(QString&);
    void printDebug();

    ZeroMQPublisher *getPublisher() const;
    ZeroMQSubscriber *getSubscriber() const;
    void setPublisher(ZeroMQPublisher *value);
    void setSubscriber(ZeroMQSubscriber *value);

    QString getDebugInfo() const;
    QString getName() const;

    void setDebugInfo(const QString &value);
};

#endif // MODULEP_H
