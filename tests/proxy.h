#ifndef PROXY_H
#define PROXY_H
#include <nzmqt/nzmqt.hpp>
#include <QObject>

class Proxy: public QObject
{
    Q_OBJECT

    QString host;
    nzmqt::ZMQSocket *xsub;
    nzmqt::ZMQSocket *xpub;
public:
    Proxy(QString, nzmqt::ZMQContext*);
    void bindToXSub();
    void bindToXPub();
    QString getHost() const;
public slots:
    void messageRecieved(const QList<QByteArray>&);
    void messageSended(QList<QByteArray>&);
signals:
    void messageSend(const QList<QByteArray>&);
};

#endif // PROXY_H
