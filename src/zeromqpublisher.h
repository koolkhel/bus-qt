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
    ZeroMQPublisher(nzmqt::ZMQContext*,QString bindAddress);

    void sendMessage(QString);
    void sendMessage(nzmqt::ZMQMessage*);
    void sendMessage(nzmqt::ZMQMessage *message, const QString filter);
    void sendMessage(const QByteArray message, const QString filter);

    QString getAddress() const;

    void close();

    nzmqt::ZMQSocket *getPublisher() const;

public slots:
    void messageSended(QList<QByteArray>);
signals:
    void messageSend(QList<QByteArray>);
};

#endif // ZEROMQPUBLISHER_H
