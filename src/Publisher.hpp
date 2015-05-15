#ifndef NZMQT_PUBSUBSERVER_H
#define NZMQT_PUBSUBSERVER_H

#include "SampleBase.hpp"

#include <nzmqt/nzmqt.hpp>

#include <QByteArray>
#include <QDateTime>
#include <QList>
#include <QTimer>

using namespace nzmqt;

class Publisher : public SampleBase
{
    Q_OBJECT
    typedef SampleBase super;

public:
    explicit Publisher(ZMQContext& context, const QString& address, const QString& topic, QObject* parent = 0)
        : super(parent)
        , address_(address), topic_(topic)
        , socket_(0)
    {
        socket_ = context.createSocket(ZMQSocket::TYP_PUB, this);
        socket_->setObjectName("Publisher.Socket.socket(PUB)");
    }

signals:
    void pingSent(const QList<QByteArray>& message);

protected:
    void startImpl()
    {
        socket_->bindTo(address_);
        QTimer::singleShot(1000, this, SLOT(sendPing()));
    }

protected slots:
    void sendPing()
    {
        static quint64 counter = 0;
        QList< QByteArray > msg;
        msg += topic_.toLocal8Bit();
        msg += QString("MSG[%1: %2]").arg(++counter).arg(QDateTime::currentDateTime().toLocalTime().toString(Qt::ISODate)).toLocal8Bit();
        try {
            socket_->sendMessage(msg,ZMQSocket::SND_NOBLOCK);
        }
        catch (const nzmqt::ZMQException& ex)
        {
            qWarning() << Q_FUNC_INFO << "Exception: Num: " << ex.num() <<" What: "<<ex.what();
        }
        qDebug() << "Publisher> " << msg;
        emit pingSent(msg);
        QTimer::singleShot(1000, this, SLOT(sendPing()));
    }

private:
    QString address_;
    QString topic_;

    ZMQSocket* socket_;
};

#endif // NZMQT_PUBSUBSERVER_H
