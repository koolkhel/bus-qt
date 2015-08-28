#include "sendlogpluginfactory.h"

#include "sendlog.h"

SENDLOGPluginFactory::SENDLOGPluginFactory()
{

}

Module *SENDLOGPluginFactory::createModule(QObject *parent)
{
    return new SENDLOG(parent);
}

QString SENDLOGPluginFactory::getModuleType()
{
    return "sendlog";
}
