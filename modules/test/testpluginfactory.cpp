#include "testpluginfactory.h"

#include "test.h"

TestPluginFactory::TestPluginFactory()
{

}

QString TestPluginFactory::getModuleType()
{
    return "test_module";
}

Module* TestPluginFactory::createModule(QObject *parent)
{
    return new TestModule();
}
