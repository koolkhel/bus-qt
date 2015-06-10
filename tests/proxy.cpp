#include "proxy.h"


Proxy::Proxy(nzmqt::ZMQSocket *publisher, nzmqt::ZMQSocket *subscriber)
{
    this->xPublisher = publisher;
    this->xSubscriber = subscriber;
}

void Proxy::run()
{
    nzmqt::proxyFromTo(xPublisher, xSubscriber);
}







