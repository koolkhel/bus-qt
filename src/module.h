#ifndef MODULE_H
#define MODULE_H
#include <QString>
#include <QMap>
#include "modulep.h"

class Module : public QObject
{
    Q_OBJECT
    QMap<QString, QString> configuration;
public:
    Module();
    Module(QMap<QString, QString>& configuration, QString);
    Module(QString);
    ~Module() = 0;
    ModuleP *getMod_p() const;
    QString name;
    void setMod_p(ModuleP *value);

    void configure(QMap<QString, QString>&);
    void start();
    void stop();
    //virtual ~Module();

private:
    ModuleP *mod_p;
};

#endif // MODULE_H








