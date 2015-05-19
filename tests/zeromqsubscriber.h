#ifndef ZEROMQSUBSCRIBER_H
#define ZEROMQSUBSCRIBER_H

#include <QObject>
#include <nzmqt/nzmqt.hpp>
#include <QString>

class ZeroMQSubscriber: public QObject
{
    Q_OBJECT
    nzmqt::ZMQSocket* subscriber;
public:
    ZeroMQSubscriber(nzmqt::ZMQContext*);
    void subscribeTo(QString,QString);

    void close();
signals:
    void recieved();
public slots:
    void messageRecieved(const QList<QByteArray>&);
};

#endif // ZEROMQSUBSCRIBER_H
