#ifndef TESTPLUGINFACTORY_H
#define TESTPLUGINFACTORY_H

#include "pluginmodulefactory.h"

class TestPluginFactory : public PluginModuleFactory
{
    Q_OBJECT
    Q_INTERFACES(PluginModuleFactory)
    Q_PLUGIN_METADATA(IID PMF_id FILE "test.json")
public:
    TestPluginFactory();

    virtual Module *createModule(QObject *parent = 0);
    virtual QString getModuleType();
};

#endif // TESTPLUGINFACTORY_H
