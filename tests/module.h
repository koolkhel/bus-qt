#ifndef MODULE_H
#define MODULE_H
#include <QString>
#include "modulep.h"

class Module : public QObject
{
    Q_OBJECT

    QString name;

public:
    Module(QMap<String key, String val> configuration);
    Module(QString);
private:
    Module_p *mod_p;
};

#endif // MODULE_H
