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
    ZeroMQSubscriber(nzmqt::ZMQContext*, QObject *parent = 0);
    virtual ~ZeroMQSubscriber() {}

    nzmqt::ZMQSocket *getSubscriber() const;
    //bool recieve(nzmqt::ZMQMessage *message);
    void close();
signals:
    void recieved();
    void message(const QList<QByteArray>&);
public slots:
    void messageRecieved(const QList<QByteArray>&);

    void start();
    void connectTo(QString address);
    void subscribe(QString subscriberFilter);
private:
    nzmqt::ZMQContext *_context;
};

#endif // ZEROMQSUBSCRIBER_H
