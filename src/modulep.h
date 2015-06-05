#ifndef MODULEP_H
#define MODULEP_H
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class ModuleP
{

    QString debugInfo;

public:
    ZeroMQPublisher *publisher;
    ZeroMQSubscriber *subscriber;
    ModuleP(QString&);
    void printDebug();
    ZeroMQPublisher *getPublisher() const;
    void setPublisher(ZeroMQPublisher *value);
    ZeroMQSubscriber *getSubscriber() const;
    void setSubscriber(ZeroMQSubscriber *value);

    QString getDebugInfo() const;
    void setDebugInfo(const QString &value);

    QString getName() const;

};

#endif // MODULEP_H
