#include "sendlog.h"

Q_LOGGING_CATEGORY(SENDLOGC, "sendlog")

SENDLOG::SENDLOG(QObject *parent)
{
    setParent(parent);

    this->name = "sendlog works";

    qCDebug(SENDLOGC, "hello,world");
}

SENDLOG::~SENDLOG()
{

}

QStringList SENDLOG::getPubTopics()
{
    QStringList topics;

    return topics;
}

void SENDLOG::respond(QString topic, indigo::pb::internal_msg &message)
{
    QString str;
    QByteArray qba = str.toLocal8Bit();
    socket->writeDatagram(qba.data(), qba.size(), QHostAddress::Broadcast, logPort);
}

void SENDLOG::read()
{
    printf("hello");
}

void SENDLOG::start()
{
    logPort = getConfigurationParameter("logPort", 45000).toInt();

    socket = new QUdpSocket(this);
     socket->bind(QHostAddress::Any, logPort);
     // тут еще какой то код конструктора //
     connect(socket, SIGNAL(readyRead()), SLOT(read()));

}

void SENDLOG::stop()
{
}
