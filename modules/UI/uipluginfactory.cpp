#include "uipluginfactory.h"
#include "uimodule.h"

UiPluginFactory::UiPluginFactory()
{

}

Module* UiPluginFactory::createModule(QObject *parent)
{
    //return new UiModule(parent);
}

QString UiPluginFactory::getModuleType()
{
    return "UI";
}

