#include "skelpluginfactory.h"

#include "skel.h"

SkelPluginFactory::SkelPluginFactory()
{

}

Module *SkelPluginFactory::createModule(QObject *parent)
{
    return new Skel(parent);
}

QString SkelPluginFactory::getModuleType()
{
    return "skel";
}
