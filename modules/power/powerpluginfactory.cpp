#include "powerpluginfactory.h"

#include "power.h"

POWERPluginFactory::POWERPluginFactory()
{

}

Module *POWERPluginFactory::createModule(QObject *parent)
{
    return new POWER(parent);
}

QString POWERPluginFactory::getModuleType()
{
    return "power";
}
