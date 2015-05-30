#ifndef MODULE_H
#define MODULE_H
#include <QString>
#include <QMap>
#include "modulep.h"

class Module : public QObject
{
    Q_OBJECT
    QString name;

public:
    Module();
    Module(QMap<QString, QString> configuration);
    Module(QString);
    ~Module() = 0;
    ModuleP *getMod_p() const;
    void setMod_p(ModuleP *value);

private:
    ModuleP *mod_p;
};

#endif // MODULE_H
