#ifndef PLUGINMODULEFACTORY_H
#define PLUGINMODULEFACTORY_H

#include <QObject>

class Module;

class PluginModuleFactory : public QObject
{
    Q_OBJECT
public:
    explicit PluginModuleFactory(QObject *parent = 0);

    virtual Module *createModule();
signals:

public slots:
};

#define PMF_id "ru.indigosystem.cars.pluginfactory"

Q_DECLARE_INTERFACE(PluginModuleFactory, PMF_id)

#endif // PLUGINMODULEFACTORY_H
