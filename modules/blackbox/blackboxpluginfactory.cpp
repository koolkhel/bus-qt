#include "blackboxpluginfactory.h"

#include "blackbox.h"

BLACKBOXPluginFactory::BLACKBOXPluginFactory()
{

}

Module *BLACKBOXPluginFactory::createModule(QObject *parent)
{
    return new BLACKBOX(parent);
}

QString BLACKBOXPluginFactory::getModuleType()
{
    return "blackbox";
}
