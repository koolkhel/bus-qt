#ifndef MODULEP_H
#define MODULEP_H

#include <QObject>

#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"

class ModuleP : public QObject
{
    Q_OBJECT
    friend class Dispatcher;

public:
    ModuleP(QString &name);
    virtual ~ModuleP() {}

    void printDebug();

    QString getDebugInfo() const;
    QString getName() const;

    void setDebugInfo(const QString &value);

signals:
    void messageReceived(const QList<QByteArray> &);
private:
    // только диспетчеру
    ZeroMQPublisher *getPublisher() const;
    ZeroMQSubscriber *getSubscriber() const;

    void setPublisher(ZeroMQPublisher *value);
    void setSubscriber(ZeroMQSubscriber *value);

    ZeroMQPublisher *publisher;
    ZeroMQSubscriber *subscriber;

    QString debugInfo;
};

#endif // MODULEP_H
