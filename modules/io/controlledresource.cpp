#include "controlledresource.h"

ControlledResource::ControlledResource(QSharedPointer<AbstractResource> resource, int timeout, QObject *parent)  : QObject(parent)
{
    rsc = resource;

    connect(&timer, SIGNAL(timeout()), this, SLOT(read()));
    connect(this, SIGNAL(write(QByteArray)), &(*rsc), SLOT(write(QByteArray)));

    timer.setSingleShot(false);
    timer.start(timeout);
}

void ControlledResource::read()
{
    QByteArray data = rsc->read();

    if(data.size()) {
        Q_EMIT dataReady(data);
    }
}

QString ControlledResource::getName()
{
    return rsc->getName();
}

