#include "proxy.h"


Proxy::Proxy(nzmqt::ZMQContext *context)
{
    this->context = context;
    this->hostPublisher = "tcp://127.0.0.1:4000";
    this->hostSubscriber = "tcp://127.0.0.1:4001";
}

Proxy::Proxy(nzmqt::ZMQContext *context, QString hostPublisher, QString hostSubscriber)
{
    this->context = context;
    this->hostPublisher = hostPublisher;
    this->hostSubscriber = hostSubscriber;
}

void Proxy::run()
{
    this->xPublisher = context->createSocket(nzmqt::ZMQSocket::TYP_XPUB);
    this->xSubscriber = context->createSocket(nzmqt::ZMQSocket::TYP_XSUB);

    this->xPublisher->bindTo(hostPublisher);
    this->xSubscriber->bindTo(hostSubscriber);

    if(xPublisher && xSubscriber) {
        nzmqt::ZMQSocket::proxyFromTo(xSubscriber, xPublisher);
    }

}

// прокси подписывается, модуль публикует
// sub -> connectTo -> xpub
void Proxy::registerSubscriber(nzmqt::ZMQSocket *moduleSubscriber)
{
    moduleSubscriber->connectTo(hostPublisher);
}

// модуль подписываетcя, прокси публикует
// xsub <- connectTo <- pub
void Proxy::registerPublisher(nzmqt::ZMQSocket *modulePublisher)
{
    modulePublisher->connectTo(this->hostSubscriber);
}
