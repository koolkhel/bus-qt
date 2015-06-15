#include "proxy.h"



Proxy::Proxy()
{
    context = nzmqt::createDefaultContext();
    this->xPublisher = context->createSocket(nzmqt::ZMQSocket::TYP_XPUB);
    this->xSubscriber = context->createSocket(nzmqt::ZMQSocket::TYP_XSUB);
}

Proxy::Proxy(QString hostPublisher, QString hostSubscriber)
{
    context = nzmqt::createDefaultContext();
    this->xPublisher = context->createSocket(nzmqt::ZMQSocket::TYP_XPUB);
    this->xSubscriber = context->createSocket(nzmqt::ZMQSocket::TYP_XSUB);
    this->xPublisher->bindTo(hostPublisher);
    this->xSubscriber->bindTo(hostSubscriber);
}

Proxy::Proxy(nzmqt::ZMQSocket *publisher, nzmqt::ZMQSocket *subscriber)
{
    this->xPublisher = publisher;
    this->xSubscriber = subscriber;
}



void Proxy::run()
{
    if(xPublisher && xSubscriber) {
        nzmqt::ZMQSocket::proxyFromTo(xPublisher, xSubscriber);
    }

}







