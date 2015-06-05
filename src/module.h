#ifndef MODULE_H
#define MODULE_H
#include <QString>
#include <QMap>
#include "modulep.h"

class Module : public QObject
{
    Q_OBJECT

public:
    Module();

    void configure(QMap<QString, QString> configuration);

    void start();
    void stop();

    virtual ~Module();

    const QString name() { return _name; }

private:
    ModuleP *mod_p;
protected:
    QString _name;
};

#endif // MODULE_H
