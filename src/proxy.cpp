#include "proxy.h"


Proxy::Proxy(nzmqt::ZMQContext *context)
{
    this->context = context;
}

Proxy::Proxy(nzmqt::ZMQContext *context,QString hostPublisher, QString hostSubscriber)
{
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
        nzmqt::ZMQSocket::proxyFromTo(xPublisher, xSubscriber);
    }

}

// прокси подписывается, модуль публикует
// xsub -> connectTo -> pub
void Proxy::subscribeTo(QString zmqBindAddress, QString topic)
{
    this->xSubscriber->connectTo(zmqBindAddress);
    this->xSubscriber->subscribeTo(topic);
}

// модуль подписываетcя, прокси публикует
// sub -> connectTo -> xpub
void Proxy::registerPublisher(nzmqt::ZMQSocket *moduleSubscriber)
{
    moduleSubscriber->connectTo(this->hostPublisher);
}





