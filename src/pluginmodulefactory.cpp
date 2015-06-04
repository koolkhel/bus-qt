#include "pluginmodulefactory.h"

PluginModuleFactory::PluginModuleFactory(QObject *parent) : QObject(parent)
{

}

Module *PluginModuleFactory::createModule()
{
    return NULL;
}
