#ifndef PROXY_H
#define PROXY_H
#include <nzmqt/nzmqt.hpp>
#include <QThread>

class Proxy: public QThread
{
    Q_OBJECT
public:
    Proxy(nzmqt::ZMQContext* context);
    Proxy(nzmqt::ZMQContext* context, QString hostPublisher, QString hostSubscriber);

    virtual void run();

    // прокси подписывается, модуль публикует
    // xsub -> connectTo -> pub
    void subscribeTo(QString zmqBindAddress, QString topic);

    // модуль подписываетcя, прокси публикует
    // sub -> connectTo -> xpub
    void registerPublisher(nzmqt::ZMQSocket *moduleSubscriber);

private:
    nzmqt::ZMQSocket *xPublisher;
    nzmqt::ZMQSocket *xSubscriber;
    QString hostPublisher;
    QString hostSubscriber;
    nzmqt::ZMQContext* context;

signals:
    void resultReady(const QString &s);
};

#endif // PROXY_H
