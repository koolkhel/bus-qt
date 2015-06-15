#include "proxy.h"



Proxy::Proxy()
{
    this->xPublisher = NULL;
    this->xSubscriber = NULL;
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







