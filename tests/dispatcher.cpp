#include "dispatcher.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"
#include <QThread>

/*
PUB PUB PUB

    XSUB

  zmq_proxy

    XPUB

SUB SUB SUB
*/

Dispatcher::Dispatcher()
{
    context = nzmqt::createDefaultContext();
    modules.insert("GPS","HelloGPS");
    modules.insert("GEOCOORD","HelloGEOCOORD");

    QThread *thr = new QThread(this);
    // запустить zmq_proxy в отдельном потоке, выделить ему адреса, публиковать и подписываться только на zmq_proxy
}

Dispatcher::~Dispatcher()
{
    context->stop();
}

Module *Dispatcher::addModule(module, name)
{
    Module_p *mod_p = module->mod_p();
    mod_p->pub = new ZeroMQPublisher(QString(адрес xsub из zmq_proxy), context);
    mod_p->sub = new ZeroMQSubscriber(context);
    module->d = this; // хз как ссылку передать, не указатель

    connect(mod_p->sub, SIGNAL(newMessage(QByteArray)), module, SLOT(dispatchModule()));


    QThread *publisherThread = new QThread;
    publisher->moveToThread(publisherThread);
    publisherThread->start();
}

void Dispatcher::publish(Module, Data, topic)
{
    Publisher *p = module->mod_p->pub;
    assert(p != NULL);

    p->sendMessage(message);
    QString message = modules.value(key);
}

void Dispatcher::dispatch()
{

}
