#ifndef TESTCLASS_H
#define TESTCLASS_H
#include <nzmqt/nzmqt.hpp>
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class testclass : public QObject
{
    public:
        testclass(QObject *parent=0);
        bool test();

    private:
        ZeroMQSubscriber* subscriber;
        ZeroMQPublisher* publisher;
};

#endif // TESTCLASS_H
