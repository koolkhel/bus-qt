#include <QThread>
#include <QSettings>
#include <QDir>
#include <QPluginLoader>

#include "dispatcher.h"
#include "modulep.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"
#include "module.h"
#include "pluginmodulefactory.h"
#include "modulep.h"
#include "proxy.h"


Dispatcher::Dispatcher() : freePort(5555), proxyXPub("tcp://127.0.0.1:5554")
{
    context = nzmqt::createDefaultContext();
    context->start();
    //modules.insert("GPS","HelloGPS");
    //modules.insert("GEOCOORD","HelloGEOCOORD");

    QThread *proxyThread = new QThread(this);
    // запустить zmq_proxy в отдельном потоке, выделить ему адреса, публиковать и подписываться только на zmq_proxy
    proxy = new Proxy();
    proxy->moveToThread(proxyThread);
    proxy->start();


}

Dispatcher::~Dispatcher()
{
    context->stop();
}

#if 0
void Dispatcher::publish(QByteArray data, QString topic)
{
    Module *module = modules[topic];
    if (module) {
        ZeroMQPublisher *publisher = module->getMod_p()->getPublisher();
        QThread *publisherThread = new QThread;
        publisher->moveToThread(publisherThread);
        publisherThread->start();

        publisher->sendMessage(data);
    }

}

Module *Dispatcher::addModule(Module *module, QString name)
{
    ModuleP *mod_p = module->getMod_p();

    //module->d = this; // хз как ссылку передать, не указатель

    connect(mod_p->subscriber, SIGNAL(newMessage(QByteArray)), module, SLOT(dispatchModule()));

    modules.insert(name,module);
}
#endif

QString Dispatcher::getFreePublisherEndpoint()
{
    return QString("tcp://127.0.0.1:%1").arg(freePort++);
}

void Dispatcher::startAll()
{
    foreach (QString instanceName, moduleInstances.keys()) {
        Module *module = moduleInstances.find(instanceName).value();

        ModuleP *mod_p = new ModuleP(instanceName);

        QString endPoint = getFreePublisherEndpoint();
        mod_p->setPublisher(new ZeroMQPublisher(context, endPoint));

        // подписал прокси на endPoint
        proxy->subscribeTo(endPoint);
        ZeroMQSubscriber *sub = new ZeroMQSubscriber(context);
        mod_p->setSubscriber(sub);

        module->start();
    }
}

void Dispatcher::subscribe(Module *module, QString topicName)
{
    module->subscribe(topicName);
   // ModuleP *mod_p = module->mod_p;
    //mod_p->getSubscriber()->subscribeTo(proxyXPub, topicName);
}

void Dispatcher::initializeAll(QString configurationFilePath)
{
    loadAllPlugins();

    QSettings iniFile(configurationFilePath, QSettings::IniFormat);

    iniFile.beginGroup("modules");
    QStringList modules = iniFile.childKeys();
    iniFile.endGroup();

    foreach (QString key, modules) {
        QVariant value = iniFile.value(key);

        QString moduleName = value.toString();
        QString instanceName = key;

        QMap<QString, QVariant> configuration;
        readConfiguration(iniFile, instanceName, configuration);

        Module *new_instance = NULL;
        PluginModuleFactory *factory = NULL;
        QMap<QString, PluginModuleFactory *>::const_iterator i = pluginFactories.find(moduleName);
        while (i != pluginFactories.end() && i.key() == moduleName) {
            factory = i.value();
        }
        if (factory == NULL) {
            // FIXME
            throw "cannot create module";
        }

        new_instance = factory->createModule(this);
        new_instance->configure(configuration,this);
        moduleInstances.insert(instanceName, new_instance);
    }
}

void Dispatcher::readConfiguration(QSettings &settings, QString moduleInstanceName,QMap<QString, QVariant> &configuration)
{
    settings.beginGroup(moduleInstanceName);
    foreach (QString parameterName, settings.childKeys()) {
        configuration.insert(parameterName, settings.value(parameterName));
    }

    settings.endGroup();
}

 void Dispatcher::loadAllPlugins()
 {
     QDir pluginDir("../modules/bin");
     QStringList pluginsFilter;
     pluginsFilter << "*.so";
     pluginDir.setNameFilters(pluginsFilter);

     foreach (QString pluginFilePath, pluginDir.entryList()) {
         QPluginLoader loader(pluginFilePath);
         QJsonObject metadata = loader.metaData();
         //printf("%s\n", qPrintable(metadata.keys().join(",")));
         //printf("%s\n", qPrintable(metadata.value("IID").toString()));

         bool result = loader.load();
         //ASSERT_TRUE(result);
         //printf("%s\n", qPrintable(loader.errorString()));

         QObject *obj = loader.instance();

         PluginModuleFactory *factory = qobject_cast<PluginModuleFactory *>(obj);
         pluginFactories.insert(factory->getModuleType(), factory);
     }
 }
