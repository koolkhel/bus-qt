#include "uipluginfactory.h"

#include "uimodule.h"
#include <QString>

UiPluginFactory::UiPluginFactory()
{

}

QString UiPluginFactory::getModuleType()
{
    return "UI";
}

Module* UiPluginFactory::createModule(QObject *parent)
{
    return new UiModule();
}




