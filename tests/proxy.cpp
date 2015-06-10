#include "proxy.h"


Proxy::Proxy(nzmqt::ZMQSocket *publisher, nzmqt::ZMQSocket *subscriber)
{
    this->publisher = publisher;
    this->subscriber = subscriber;
}

void Proxy::run()
{
    nzmqt::proxyFromTo(publisher, subscriber);
}







