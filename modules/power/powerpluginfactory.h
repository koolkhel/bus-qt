#ifndef SKELPLUGINFACTORY_H
#define SKELPLUGINFACTORY_H

#include "pluginmodulefactory.h"

class POWERPluginFactory : public PluginModuleFactory
{
    Q_OBJECT
    Q_INTERFACES(PluginModuleFactory)
    Q_PLUGIN_METADATA(IID PMF_id FILE "power.json")

public:
    POWERPluginFactory();

    virtual Module *createModule(QObject *parent = 0);
    virtual QString getModuleType();
};

#endif // SKELPLUGINFACTORY_H
