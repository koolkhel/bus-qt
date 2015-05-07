#include "socket.h"
#include <QByteArray>
#include <QList>

using namespace nzmqt;

Socket::Socket(QObject* parent) :
QThread(parent)
{
    m_address = "tcp://127.0.0.1:8888";
    ZMQContext* context = createDefaultContext(this);
    context->start();

    m_socket = context->createSocket(ZMQSocket::TYP_PUSH);

    topic_ = "Hello";
    r_address = "tcp://127.0.0.1:8888";
    r_socket = context->createSocket(ZMQSocket::TYP_SUB);

    connect(r_socket, SIGNAL(messageReceived(const QList<QByteArray>&)), SLOT(messageReceived(const QList<QByteArray>&)));
    connect(this, SIGNAL(stringSent(QList<QByteArray>)),SLOT(stringSended(const QList<QByteArray>&)));
    timerout = new QTimer(this);
    timerout->setInterval(2500);
    timerout->setSingleShot(true);
}

Socket::~Socket()
{
    client->stop();
}

void Socket::run()
{
    m_socket->connectTo(m_address);
    QTimer::singleShot(1000, this, SLOT(sendMessage()));

    r_socket->subscribeTo(topic_);
    r_socket->connectTo(r_address);

    timerout->start();
    this->exec();
}

void Socket::stop()
{
    timerout->stop();
    m_socket->close();
    this->quit();
}

void Socket::send(QString message)
{
    this->message = message;
}

void Socket::sendMessage()
{
    QList<QByteArray> msg;
    msg+= message.toLocal8Bit();
    m_socket->sendMessage(msg);
    emit stringSent(msg);
    QTimer::singleShot(0, this, SLOT(stop()));
}

void Socket::stringSended(const QList<QByteArray> &message)
{
    qDebug()<<"Send: "<<message;
}

void Socket::messageReceived(const QList<QByteArray>& message)
{
    qDebug() << "Recieved" <<message;
}
