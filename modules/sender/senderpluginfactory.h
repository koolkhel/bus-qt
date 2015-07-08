#ifndef SKELPLUGINFACTORY_H
#define SKELPLUGINFACTORY_H

#include "pluginmodulefactory.h"

class SENDERPluginFactory : public PluginModuleFactory
{
    Q_OBJECT
    Q_INTERFACES(PluginModuleFactory)
    Q_PLUGIN_METADATA(IID PMF_id FILE "sender.json")

public:
    SENDERPluginFactory();

    virtual Module *createModule(QObject *parent = 0);
    virtual QString getModuleType();
};

#endif // SKELPLUGINFACTORY_H
