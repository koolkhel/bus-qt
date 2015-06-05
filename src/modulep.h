#ifndef MODULEP_H
#define MODULEP_H
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class ModuleP
{  
    public:
        ZeroMQPublisher *publisher;
        ZeroMQSubscriber *subscriber;

        ModuleP(QString&);
        void printDebug();
        ZeroMQPublisher *getPublisher() const;
        void setPublisher(ZeroMQPublisher *value);
        ZeroMQSubscriber *getSubscriber() const;
        void setSubscriber(ZeroMQSubscriber *value);
};

#endif // MODULEP_H
