#include "vpnremotepluginfactory.h"

#include "vpnremote.h"

VPNREMOTEPluginFactory::VPNREMOTEPluginFactory()
{

}

Module *VPNREMOTEPluginFactory::createModule(QObject *parent)
{
    return new VPNREMOTE(parent);
}

QString VPNREMOTEPluginFactory::getModuleType()
{
    return "vpnremote";
}
