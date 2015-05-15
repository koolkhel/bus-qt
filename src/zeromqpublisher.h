#ifndef ZEROMQPUBLISHER_H
#define ZEROMQPUBLISHER_H
#include <QObject>
#include <nzmqt/nzmqt.hpp>

class ZeroMQPublisher: public QObject
{
    Q_OBJECT

    QString address;
    QString filter;
    nzmqt::ZMQSocket* publisher;

public:
    ZeroMQPublisher(QString,QString);
    void sendMessage(QString);

    QString getFilter() const;
    void setFilter(const QString &value);

    QString getAddress() const;
    void setAddress(const QString &value);

public slots:
    void messageSended(QByteArray);
signals:
    void messageSend(QByteArray);
};

#endif // ZEROMQPUBLISHER_H
