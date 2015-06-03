#include "proxy.h"

Proxy::Proxy(QString host, nzmqt::ZMQContext *context)
{
    this->host = host;
    xpub = context->createSocket(nzmqt::ZMQSocket::TYP_XPUB);
    xpub->bindTo(host);

    xsub = context->createSocket(nzmqt::ZMQSocket::TYP_XSUB);
    xsub->bindTo(host);


    connect(xsub, SIGNAL(messageReceived(const QList<QByteArray>&)),this, SLOT(messageReceived(const QList<QByteArray>&)));
    connect(this, SIGNAL(messageSend(const QList<QByteArray>&)),this,SLOT(messageSended(QList<QByteArray>&)));

}


QString Proxy::getHost() const
{
    return host;
}

void Proxy::messageRecieved(const QList<QByteArray>& array)
{
    xpub->sendMessage(array);
    emit messageSend(array);
}

void Proxy::messageSended(QList<QByteArray>& array)
{

}





