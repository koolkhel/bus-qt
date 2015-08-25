#include "logspluginfactory.h"

#include "logs.h"

LOGSPluginFactory::LOGSPluginFactory()
{

}

Module *LOGSPluginFactory::createModule(QObject *parent)
{
    return new LOGS(parent);
}

QString LOGSPluginFactory::getModuleType()
{
    return "logs";
}
