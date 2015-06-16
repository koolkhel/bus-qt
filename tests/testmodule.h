#ifndef TESTMODULE_H
#define TESTMODULE_H
#include "module.h"

#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class TestModule: public Module
{
public:
    TestModule();
    void test_step();

private:
    ZeroMQSubscriber* subscriber;
    ZeroMQPublisher* publisher;
};

#endif // TESTMODULE_H
