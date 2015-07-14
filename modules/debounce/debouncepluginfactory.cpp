#include "debouncepluginfactory.h"

#include "debounce.h"

DEBOUNCEPluginFactory::DEBOUNCEPluginFactory()
{

}

Module *DEBOUNCEPluginFactory::createModule(QObject *parent)
{
    return new DEBOUNCE(parent);
}

QString DEBOUNCEPluginFactory::getModuleType()
{
    return "debounce";
}
