#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QMap>
#include <QString>
#include <QList>
#include <QVariant>
#include <functional>
#include <QObject>
#include <map>

#include "module.h"
#include "topic.h"
#include "context.h"
#include "pluginmodulefactory.h"

class Dispatcher : public QObject
{
    Q_OBJECT

    friend class ModuleP;
    friend class Module;

public:
    Dispatcher();
    virtual ~Dispatcher();

    void initializeAll(QString configurationFilePath);

    void startAll();

    //Module* addModule(Module *,QString);
    //void publish(Module *mod, QByteArray Data, QString Topic);

    void subscribe(Module *module, QString topicName);
private:
    Context *context;

    void readConfiguration(QSettings &settings, QString moduleInstanceName,
                           QMap<QString, QVariant> &configuration);

    void loadAllPlugins();

    QString getFreePublisherEndpoint();

    int freePort;

    // тип-модуля - фабрика
    QMap<QString, PluginModuleFactory *> pluginFactories;

    // имя-модуля - модуль
    QMap<QString, Module *> moduleInstances;\

    //QString proxyXSub;

    QString proxyXPub;
};

#endif // DISPATCHER_H
