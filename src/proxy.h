#ifndef PROXY_H
#define PROXY_H
#include <nzmqt/nzmqt.hpp>
#include <QThread>

class Proxy: public QThread
{
    Q_OBJECT

public:
    Proxy();
    Proxy(QString host, QString pub);
    Proxy(nzmqt::ZMQSocket *publisher, nzmqt::ZMQSocket *subscriber);
    void run();
    void subscribeTo(QString host);
private:
    nzmqt::ZMQContext *context;
    nzmqt::ZMQSocket *xPublisher;
    nzmqt::ZMQSocket *xSubscriber;
 signals:
    void resultReady(const QString &s);
};

#endif // PROXY_H
