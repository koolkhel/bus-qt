#include "modulepluginfactory.h"

#include "module.h"

MODULEPluginFactory::MODULEPluginFactory()
{

}

Module *MODULEPluginFactory::createModule(QObject *parent)
{
    return new MODULE(parent);
}

QString MODULEPluginFactory::getModuleType()
{
    return "module";
}
