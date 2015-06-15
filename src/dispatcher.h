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
#include "topic.h"
#include "context.h"
#include "pluginmodulefactory.h"
#include "proxy.h"

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    Dispatcher();

    virtual ~Dispatcher();

    void initializeAll(QString configurationFilePath);

    void startAll();

    //Module* addModule(Module *,QString);
    //void publish(Module *mod, QByteArray Data, QString Topic);

    void subscribe(Module *module, QString topicName);
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
};

#endif // DISPATCHER_H
