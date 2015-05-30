#ifndef TESTMODULE_H
#define TESTMODULE_H
#include "module.h"

class TestModule: public Module
{
public:
    TestModule();
    void test_step();
};

#endif // TESTMODULE_H
