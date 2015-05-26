#ifndef ZEROMQPUBLISHER_H
#define ZEROMQPUBLISHER_H
#include <QObject>
#include <nzmqt/nzmqt.hpp>

class ZeroMQPublisher: public QObject
{
    Q_OBJECT
    QString address;
    nzmqt::ZMQSocket *publisher;

public:
    ZeroMQPublisher(QString,nzmqt::ZMQContext*);
    void sendMessage(QString);

    QString getAddress() const;

    void close();

    nzmqt::ZMQSocket *getPublisher() const;

public slots:
    void messageSended(QByteArray);
signals:
    void messageSend(QByteArray);
};

#endif // ZEROMQPUBLISHER_H
