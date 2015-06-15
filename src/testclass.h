#ifndef TESTCLASS_H
#define TESTCLASS_H
#include <nzmqt/nzmqt.hpp>
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class testclass : public QObject
{
    ZeroMQSubscriber* subscriber;
    ZeroMQPublisher* publisher;
public:
    testclass(QObject *parent=0);
    bool test();
};

#endif // TESTCLASS_H
