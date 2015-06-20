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
    ZeroMQSubscriber(nzmqt::ZMQContext*);
    virtual ~ZeroMQSubscriber() {}

    void subscribeTo(QString address,QString subscriberFilter);
    nzmqt::ZMQSocket *getSubscriber() const;
    bool recieve(nzmqt::ZMQMessage *message);
    void close();
signals:
    void recieved();
    void message(const QList<QByteArray>&);
public slots:
    void messageRecieved(const QList<QByteArray>&);
};

#endif // ZEROMQSUBSCRIBER_H
