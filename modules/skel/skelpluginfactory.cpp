#include "skelpluginfactory.h"

#include "skel.h"

SkelPluginFactory::SkelPluginFactory()
{

}

Module *SkelPluginFactory::createModule()
{
    return new Skel();
}
