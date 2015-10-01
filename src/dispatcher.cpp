#include <QThread>
#include <QSettings>
#include <QDir>
#include <QPluginLoader>
#include <QFile>
#include <QTextStream>

#include "dispatcher.h"
#include "modulep.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"
#include "module.h"
#include "pluginmodulefactory.h"
#include "modulep.h"
#include "proxy.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(ZMQ, "zmq")

Dispatcher::Dispatcher() : freePort(5555), proxyXPub("tcp://127.0.0.1:5554")
{
    sampleId = 1;

    context = nzmqt::createDefaultContext();
    context->start();

    // запустить zmq_proxy в отдельном потоке, выделить ему адреса, публиковать и подписываться только на zmq_proxy
    //proxy = new Proxy(context, "tcp://127.0.0.1:5000", "tcp://127.0.0.1:5001");
    proxy = new Proxy(context, "inproc://xpub", "inproc://xsub");
    proxy->start();
}

Dispatcher::~Dispatcher()
{
    context->stop();
}


void Dispatcher::publish(ModuleP *modP, ::indigo::pb::internal_msg &msg, QString topic)
{
    assert(modP != NULL);
    assert(modP->getPublisher() != NULL);

    if (!msg.has_id()) {
        msg.set_id(sampleId++);
    }

    QByteArray data = QByteArray::fromStdString(msg.SerializeAsString());

    QMetaObject::invokeMethod(modP->getPublisher(), "sendMessage", Qt::QueuedConnection,
                              Q_ARG(QByteArray, data), Q_ARG(QString, topic));
}

QString Dispatcher::getFreePublisherEndpoint()
{
    return QString("tcp://127.0.0.1:%1").arg(freePort++);
    //return QString("inproc://module%1").arg(freePort++);
}

void Dispatcher::startAll()
{
    //QThread::currentThread()->setObjectName("main_thread");
    foreach (QString instanceName, moduleInstances.keys()) {
        Module *module = moduleInstances.find(instanceName).value();
        bool separateThread = module->getConfigurationParameter("thread", "false").toBool();
        if (separateThread) {
            QThread *thread = new QThread(this);
            module->moveToThread(thread);
            thread->start();
        }

        ModuleP *mod_p = new ModuleP(instanceName);

        QString endPoint = getFreePublisherEndpoint();
        ZeroMQPublisher *pub = new ZeroMQPublisher(context, endPoint);
        // TODO поток
        pub->moveToThread(QThread::currentThread());
        QMetaObject::invokeMethod(pub, "start", Qt::QueuedConnection);


        // подписал прокси на endPoint
        ZeroMQSubscriber *sub = new ZeroMQSubscriber(context);
        // TODO поток
        sub->moveToThread(QThread::currentThread());
        QMetaObject::invokeMethod(sub, "start", Qt::QueuedConnection);

        // publisher (модуль) -> connectTo -> xsub (проксик) <->
        // xpub (проксик) <- connectTo <- subscriber (модуль)

        QMetaObject::invokeMethod(pub, "connectTo", Qt::QueuedConnection, Q_ARG(QString, proxy->subscriberAddress()));
        QMetaObject::invokeMethod(sub, "connectTo", Qt::QueuedConnection, Q_ARG(QString, proxy->publisherAddress()));

        mod_p->setPublisher(pub);
        mod_p->setSubscriber(sub);
        module->mod_p = mod_p;

        connect(mod_p, SIGNAL(messageReceived(const QList<QByteArray> &)),
                module, SLOT(messageReceived(const QList<QByteArray>&)), Qt::QueuedConnection);

        QMetaObject::invokeMethod(module, "start", Qt::QueuedConnection);
    }
}

void Dispatcher::subscribe(Module *module, QString topicName)
{
    ModuleP *mod_p = module->mod_p;
    QMetaObject::invokeMethod(mod_p->getSubscriber(), "subscribe", Qt::QueuedConnection,
                              Q_ARG(QString, topicName));
}

// для тестов
void Dispatcher::initializeAll(QStringList configurationStrings)
{
    QFile tmpConfigFile("tmp.ini");
    tmpConfigFile.open(QIODevice::WriteOnly);

    QTextStream out(&tmpConfigFile);
    out << configurationStrings.join("\n");
    tmpConfigFile.close();

    initializeAll("tmp.ini");
}

void Dispatcher::initializeAll(QString configurationFilePath)
{
    loadAllPlugins();

    QSettings iniFile(configurationFilePath, QSettings::IniFormat);

    iniFile.beginGroup("modules");
    QStringList modules = iniFile.childKeys();
    iniFile.endGroup();

    foreach (QString key, modules) {
        iniFile.beginGroup("modules");
        QVariant value = iniFile.value(key);
        iniFile.endGroup();

        QString moduleName = value.toString();
        QString instanceName = key;

        QMap<QString, QVariant> configuration;
        readConfiguration(iniFile, instanceName, configuration);

        Module *new_instance = NULL;
        PluginModuleFactory *factory = NULL;
        QMap<QString, PluginModuleFactory *>::const_iterator i = pluginFactories.find(moduleName);
        while (i != pluginFactories.end() && i.key() == moduleName) {
            factory = i.value();
            i++;
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
         QString dir = pluginDir.absoluteFilePath(pluginFilePath);
         QPluginLoader loader(dir);
         QJsonObject metadata = loader.metaData();
         bool result = loader.load();
         //ASSERT_TRUE(result);

         if(result) {

             QObject *obj = loader.instance();

             PluginModuleFactory *factory = qobject_cast<PluginModuleFactory *>(obj);
             pluginFactories.insert(factory->getModuleType(), factory);
         } else {
             printf("%s", qPrintable(loader.errorString()));
         }
     }
 }
