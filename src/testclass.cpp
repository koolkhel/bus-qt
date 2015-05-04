#include "testclass.h"

#include "nzmqt/nzmqt.hpp"

testclass::testclass()
{
}

bool testclass::test()
{
    nzmqt::ZMQContext* context = nzmqt::createDefaultContext();

    context = 0;
    context->start();
    context->stop();
    return true;
}
