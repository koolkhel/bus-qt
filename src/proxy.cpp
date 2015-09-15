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
    //QThread::currentThread()->setObjectName("proxy_thread");
    void *context = zmq_ctx_new();
    void *frontend = zmq_socket(context, ZMQ_XPUB);
    int rc = zmq_bind(frontend, hostPublisher.toLocal8Bit());
    assert (rc == 0);

    void *backend = zmq_socket(context, ZMQ_XSUB);
    rc = zmq_bind(backend, hostSubscriber.toLocal8Bit());
    assert (rc == 0);

    rc = zmq_proxy(frontend, backend, NULL);
    assert (rc == 0);
#if 0
    this->xPublisher = context->createSocket(nzmqt::ZMQSocket::TYP_XPUB);
    this->xSubscriber = context->createSocket(nzmqt::ZMQSocket::TYP_XSUB);

    xPublisher->setLinger(0);
    xPublisher->setReceiveHighWaterMark(0);
    xSubscriber->setReceiveHighWaterMark(0);

    xPublisher->setSendHighWaterMark(0);
    xSubscriber->setSendHighWaterMark(0);
    xSubscriber->setLinger(0);

    this->xPublisher->bindTo(hostPublisher);
    this->xSubscriber->bindTo(hostSubscriber);

    if(xPublisher && xSubscriber) {
        //nzmqt::ZMQSocket::proxyFromTo(xSubscriber, xPublisher);
        nzmqt::ZMQSocket::proxyFromTo(xPublisher, xSubscriber);
    }
#endif
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
