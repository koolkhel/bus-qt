#include "dispatcher.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"
#include <QThread>


Dispatcher::Dispatcher()
{
    modules.insert("GPS","HelloGPS");
    modules.insert("GEOCOORD","HelloGEOCOORD");
}

void Dispatcher::publish(QString key)
{
    nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
    QString message  = modules.value(key);
    ZeroMQPublisher *publisher = new ZeroMQPublisher(QString("127.0.0.1"),context);
    QThread *publisherThread = new QThread;
    publisher->moveToThread(publisherThread);
    publisherThread->start();
    publisher->sendMessage(message);
}

void Dispatcher::dispatch()
{

}


