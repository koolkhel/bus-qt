#include "dispatcher.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"
#include <QThread>
#include "modulep.h"

Dispatcher::Dispatcher()
{
    context = new Context();
    //modules.insert("GPS","HelloGPS");
    //modules.insert("GEOCOORD","HelloGEOCOORD");

    QThread *thr = new QThread(this);
    // запустить zmq_proxy в отдельном потоке, выделить ему адреса, публиковать и подписываться только на zmq_proxy
}

Dispatcher::~Dispatcher()
{
    context->stop();
}

void Dispatcher::publish(QByteArray data, QString topic)
{
    Module *module = modules[topic];
    if(module)
    {
        ZeroMQPublisher *publisher = module->getMod_p()->getPublisher();
        QThread *publisherThread = new QThread;
        publisher->moveToThread(publisherThread);
        publisherThread->start();

        publisher->sendMessage(data);
    }

}

Module *Dispatcher::addModule(Module *module,QString name)
{
    ModuleP *mod_p = module->getMod_p();
    mod_p->setPublisher(new ZeroMQPublisher(context, QString("127.0.0.1:5555")));
    mod_p->setSubscriber(new ZeroMQSubscriber(context));
    //module->d = this; // хз как ссылку передать, не указатель

    connect(mod_p->subscriber, SIGNAL(newMessage(QByteArray)), module, SLOT(dispatchModule()));

    modules.insert(name,module);



}

