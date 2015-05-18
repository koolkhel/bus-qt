#ifndef NZMQT_PUBSUBCLIENT_H
#define NZMQT_PUBSUBCLIENT_H

#include "SampleBase.hpp"

#include <nzmqt/nzmqt.hpp>

#include <QByteArray>
#include <QList>


using namespace nzmqt;

class Subscriber : public SampleBase
{
    Q_OBJECT
    typedef SampleBase super;

public:
    explicit Subscriber(ZMQContext& context, const QString& address, const QString& topic, QObject *parent = 0)
        : super(parent)
        , address_(address), topic_(topic)
        , socket_(0)
    {
        socket_ = context.createSocket(ZMQSocket::TYP_SUB, this);
        socket_->setObjectName("Subscriber.Socket.socket(SUB)");
        connect(socket_, SIGNAL(messageReceived(const QList<QByteArray>&)), SLOT(messageReceived(const QList<QByteArray>&)));
    }

signals:
    void pingReceived(const QList<QByteArray>& message);

protected:
    void startImpl()
    {
        socket_->subscribeTo(topic_);
        socket_->connectTo(address_);
        socket_->setOption(ZMQSocket::OPT_SUBSCRIBE,topic_.toStdString().c_str());
    }

protected slots:
    void messageReceived(const QList<QByteArray>& message)
    {
        qDebug() << "Subscriber> " << message;
        emit pingReceived(message);
    }

private:
    QString address_;
    QString topic_;

    ZMQSocket* socket_;
};

#endif // NZMQT_PUBSUBCLIENT_H
