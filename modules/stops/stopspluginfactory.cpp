#include "stopspluginfactory.h"

#include "stops.h"

STOPSPluginFactory::STOPSPluginFactory()
{

}

Module *STOPSPluginFactory::createModule(QObject *parent)
{
    return new STOPS(parent);
}

QString STOPSPluginFactory::getModuleType()
{
    return "stops";
}
