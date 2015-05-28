#include "dispatcher.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"
#include <QThread>
#include "modulep.h"

/*
PUB PUB PUB

    XSUB

  zmq_proxy

    XPUB

SUB SUB SUB
*/

Dispatcher::Dispatcher()
{
    qRegisterMetaType<Module>("Module");
    context = nzmqt::createDefaultContext();
    //modules.insert("GPS","HelloGPS");
    //modules.insert("GEOCOORD","HelloGEOCOORD");

    QThread *thr = new QThread(this);
    // запустить zmq_proxy в отдельном потоке, выделить ему адреса, публиковать и подписываться только на zmq_proxy
}

Dispatcher::~Dispatcher()
{
    context->stop();
}



void Dispatcher::publish(Module *module, QByteArray data, QString topic)
{
    ZeroMQPublisher *p = module->getMod_p()->getPublisher();
    assert(p != NULL);

    p->sendMessage(data);
}

Module *Dispatcher::addModule(Module *module,QString name)
{
    ModuleP *mod_p = module->getMod_p();
    //Адрес xsub из zmq_proxy
    mod_p->publisher = new ZeroMQPublisher(QString("127.0.0.1"), context);
    mod_p->subscriber = new ZeroMQSubscriber(context);
    //module->d = this; // хз как ссылку передать, не указатель

    connect(mod_p->subscriber, SIGNAL(newMessage(QByteArray)), module, SLOT(dispatchModule()));


    QThread *publisherThread = new QThread;
    mod_p->publisher->moveToThread(publisherThread);
    publisherThread->start();
}

