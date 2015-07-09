#include "senderpluginfactory.h"

#include "sender.h"

SENDERPluginFactory::SENDERPluginFactory()
{

}

Module *SENDERPluginFactory::createModule(QObject *parent)
{
    return new SENDER(parent);
}

QString SENDERPluginFactory::getModuleType()
{
    return "sender";
}
