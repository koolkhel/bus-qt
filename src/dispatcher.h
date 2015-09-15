#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QMap>
#include <QString>
#include <QList>
#include <QVariant>
#include <functional>
#include <QObject>
#include <QSettings>

#include "module.h"
#include "pluginmodulefactory.h"
#include "proxy.h"

#include <QAtomicInt>

class Dispatcher : public QObject
{
    Q_OBJECT

public:
    Dispatcher();

    virtual ~Dispatcher();

    void initializeAll(QString configurationFilePath);
    void initializeAll(QStringList configurationStrings);

    void startAll();

    //Module* addModule(Module *,QString);
    //void publish(Module *mod, QByteArray Data, QString Topic);

    void subscribe(Module *module, QString topicName);

    QMap<QString, Module *> getModuleInstances() { return moduleInstances; }

    void publish(ModuleP *modP, ::indigo::pb::internal_msg &msg, QString topic);

private:
    nzmqt::ZMQContext *context;

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

    Proxy *proxy;

    QAtomicInt sampleId;
};

#endif // DISPATCHER_H
