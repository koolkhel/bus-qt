#include "gpsmodulepluginfactory.h"

#include "gpsmodule.h"

GPSMODULEPluginFactory::GPSMODULEPluginFactory()
{

}

Module *GPSMODULEPluginFactory::createModule(QObject *parent)
{
    return new GPSMODULE(parent);
}

QString GPSMODULEPluginFactory::getModuleType()
{
    return "gpsmodule";
}
