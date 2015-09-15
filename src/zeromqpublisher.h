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
    ZeroMQPublisher(nzmqt::ZMQContext*,QString bindAddress, QObject *parent = 0);

#if 0
    void sendMessage(QString);
    void sendMessage(nzmqt::ZMQMessage*);
    void sendMessage(nzmqt::ZMQMessage *message, const QString filter);
#endif

    QString getAddress() const;

    void close();

    nzmqt::ZMQSocket *getPublisher() const;

public slots:
    void start();
    void messageSended(QList<QByteArray>);
    void sendMessage(const QByteArray message, const QString filter);
    void connectTo(QString address);

signals:
    void messageSend(QList<QByteArray>);
private:
    nzmqt::ZMQContext *_context;
    QString _bindAddress;
};

#endif // ZEROMQPUBLISHER_H
