#ifndef UIPLUGINFACTORY_H
#define UIPLUGINFACTORY_H
#include "module.h"
#include "pluginmodulefactory.h"
#include <QString>

class UiPluginFactory : public PluginModuleFactory
{
    Q_OBJECT
    Q_INTERFACES(PluginModuleFactory)
public:
    UiPluginFactory();
    virtual Module *createModule(QObject *parent = 0);
    virtual QString getModuleType();
};

#endif // UIPLUGINFACTORY_H
