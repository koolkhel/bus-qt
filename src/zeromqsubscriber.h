#ifndef ZEROMQSUBSCRIBER_H
#define ZEROMQSUBSCRIBER_H

#include <QObject>
#include <nzmqt/nzmqt.hpp>
#include <QString>

class ZeroMQSubscriber: public QObject
{
    Q_OBJECT
    nzmqt::ZMQSocket *subscriber;
public:
    ZeroMQSubscriber();
    void subscribeTo(QString address, QString subscriberFilter);

signals:
    void recieved();
public slots:
    void messageRecieved(const QList<QByteArray>&);
};

#endif // ZEROMQSUBSCRIBER_H
