#include "module.h"

Module::Module(QMap<QString, QString> configuration)
{

}

Module::Module(QString name)
{
    this->name = name;
}
ModuleP *Module::getMod_p() const
{
    return mod_p;
}

void Module::setMod_p(ModuleP *value)
{
    mod_p = value;
}


