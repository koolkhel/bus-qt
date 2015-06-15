#include "proxy.h"


Proxy::Proxy(nzmqt::ZMQContext *context)
{
    this->xPublisher = context->createSocket(nzmqt::ZMQSocket::TYP_XPUB);
    this->xSubscriber = context->createSocket(nzmqt::ZMQSocket::TYP_XSUB);
}

Proxy::Proxy(nzmqt::ZMQContext *context,QString hostPublisher, QString hostSubscriber)
{
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

void Proxy::subscribeTo(QString host)
{
    this->xPublisher->bindTo(host);
    this->xSubscriber->bindTo(host);
}







