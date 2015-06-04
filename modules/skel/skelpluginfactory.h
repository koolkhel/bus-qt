#ifndef SKELPLUGINFACTORY_H
#define SKELPLUGINFACTORY_H

#include "pluginmodulefactory.h"

class SkelPluginFactory : public PluginModuleFactory
{
    Q_OBJECT
    Q_INTERFACES(PluginModuleFactory)
    Q_PLUGIN_METADATA(IID PMF_id FILE "skel.json")

public:
    SkelPluginFactory();

    virtual Module *createModule();
};

#endif // SKELPLUGINFACTORY_H
