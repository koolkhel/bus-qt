#ifndef MODULE_H
#define MODULE_H
#include <QString>
#include "modulep.h"

class Module
{
    friend class ModuleP;
    QString name;

public:
    Module();
    Module(QString);
};

#endif // MODULE_H
