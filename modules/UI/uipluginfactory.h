#ifndef UIPLUGINFACTORY_H
#define UIPLUGINFACTORY_H

#include "pluginmodulefactory.h"

class UiPluginFactory : public PluginModuleFactory
{
    Q_OBJECT
    Q_INTERFACES(PluginModuleFactory)
    Q_PLUGIN_METADATA(IID PMF_id FILE "ui.json")

    public:
        UiPluginFactory();
        virtual Module *createModule(QObject *parent = 0);
        virtual QString getModuleType();
};

#endif // UIPLUGINFACTORY_H
