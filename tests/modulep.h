#ifndef MODULEP_H
#define MODULEP_H
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class ModuleP
{
    ZeroMQPublisher *publisher;
    ZeroMQSubscriber *subscriber;
public:
    ModuleP(QString&);
    void printDebug();
};

#endif // MODULEP_H
