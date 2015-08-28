#ifndef SKELPLUGINFACTORY_H
#define SKELPLUGINFACTORY_H

#include "pluginmodulefactory.h"

class STOPSPluginFactory : public PluginModuleFactory
{
    Q_OBJECT
    Q_INTERFACES(PluginModuleFactory)
    Q_PLUGIN_METADATA(IID PMF_id FILE "stops.json")

public:
    STOPSPluginFactory();

    virtual Module *createModule(QObject *parent = 0);
    virtual QString getModuleType();
};

#endif // SKELPLUGINFACTORY_H
