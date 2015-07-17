#ifndef CONTROLLEDRESOURCE_H
#define CONTROLLEDRESOURCE_H

#include <QObject>
#include <QTimer>
#include <QSharedPointer>

#include "abstractresource.h"

class ControlledResource : public QObject
{
    Q_OBJECT
public:
    explicit ControlledResource(QSharedPointer<AbstractResource> resource,
                                int timeout = 50,
                                QObject *parent = 0);

signals:
    void dataReady(QByteArray);
    void write(QByteArray);
public slots:
    void read();
    QString getName();

private:
    QSharedPointer<AbstractResource> rsc;
    QTimer timer;
};

#endif // CONTROLLEDRESOURCE_H
