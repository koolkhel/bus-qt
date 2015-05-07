#ifndef SOCKET_H
#define SOCKET_H

#include <nzmqt/nzmqt.hpp>

#include <QByteArray>
#include <QDateTime>
#include <QList>
#include <QTimer>
#include <QObject>
#include <QThread>

namespace nzmqt
{

class Socket : public QThread
{
    Q_OBJECT

public:
    Socket(QObject *parent=0);
    ~Socket();
    void run();

public slots:
    void stop();
    void send(QString message); //receive emitted signal

signals:
    void stringSent(const QList<QByteArray>& message);


protected slots:
    void messageReceived(const QList<QByteArray>& message);
    void sendMessage();

private:
    QString message;
    QString m_address;
    QString r_address;
    QString r_address1;
    QString topic_;

    ZMQSocket* m_socket;
    ZMQSocket* r_socket;
    ZMQSocket* r_socket1;
    QTimer* timerout;
    Socket *client;
};

}
#endif // SOCKET_H
