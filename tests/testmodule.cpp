#include "testmodule.h"

TestModule::TestModule()
{
    QThread *contextThead = new QThread;
    QThread *pubThread = new QThread;
    QThread *subThread = new QThread;

    nzmqt::ZMQContext* context = nzmqt::createDefaultContext();
    context->start();
    context->moveToThread(contextThead);
    contextThead->start();

    usleep(100 * 10000);


    publisher = new ZeroMQPublisher(context,"tcp://*:5556");
    publisher->moveToThread(pubThread);
    pubThread->start();

    usleep(100 * 10000);

    subscriber = new ZeroMQSubscriber(context);
    subscriber->moveToThread(subThread);
    subThread->start();

    usleep(100 * 10000);

    subscriber->subscribeTo("tcp://localhost:5556","");

    usleep(100 * 10000);
}

void TestModule::test_step()
{
    publisher->sendMessage("Move");

    usleep(100 * 10000);
}

