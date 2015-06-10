#ifndef MODULEP_H
#define MODULEP_H

#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class ModuleP
{

public:
    ModuleP(QString &name);
    void printDebug();

    QString getDebugInfo() const;
    QString getName() const;

    void setDebugInfo(const QString &value);
    friend class Dispatcher;
private:
    // только диспетчеру
    ZeroMQPublisher *getPublisher() const;
    ZeroMQSubscriber *getSubscriber() const;

    void setPublisher(ZeroMQPublisher *value);
    void setSubscriber(ZeroMQSubscriber *value);

    ZeroMQPublisher *publisher;
    ZeroMQSubscriber *subscriber;

    QString debugInfo;
};

#endif // MODULEP_H
