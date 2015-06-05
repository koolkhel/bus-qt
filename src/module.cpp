#include "module.h"

Module::Module()
{
    this->name = "";
}

Module::Module(QMap<QString, QString>& configuration, QString name)
{
    this->configuration = configuration;
    this->name = name;
}

Module::Module(QString name)
{
    this->name = name;
}

Module::~Module()
{

}
ModuleP *Module::getMod_p() const
{
    return mod_p;
}

void Module::setMod_p(ModuleP *value)
{
    mod_p = value;
}

void Module::configure(QMap<QString, QString>& configuration)
{
    this->configuration = configuration;
}

void Module::start()
{

}

void Module::stop()
{

}


