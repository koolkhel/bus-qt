#include "iopluginfactory.h"

#include "io.h"

IOPluginFactory::IOPluginFactory()
{

}

Module *IOPluginFactory::createModule(QObject *parent)
{
    return new IO(parent);
}

QString IOPluginFactory::getModuleType()
{
    return "io";
}
