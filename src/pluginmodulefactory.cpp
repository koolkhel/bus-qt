#include "pluginmodulefactory.h"

PluginModuleFactory::PluginModuleFactory(QObject *parent) : QObject(parent)
{

}

Module *PluginModuleFactory::createModule(QObject parent)
{
    return NULL;
}

QString PluginModuleFactory::getModuleType()
{
    return "wtf";
}
