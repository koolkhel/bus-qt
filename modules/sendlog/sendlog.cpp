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
    std::string str;
    message.SerializeToString(&str);
    topic += " ";
    topic += QString::fromStdString(str);

    write(topic.toLocal8Bit());
}

void SENDLOG::read()
{
    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    socket->readDatagram(datagram.data(), datagram.size());
    write(datagram);
}

void SENDLOG::write(QByteArray data)
{
    socket->writeDatagram(data, remoteServer, logPort);
}

void SENDLOG::start()
{
    logPort = getConfigurationParameter("logPort", 45000).toInt();

    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, logPort);
    connect(socket, SIGNAL(readyRead()), SLOT(read()));

    logPort = getConfigurationParameter("serverPort", 45001).toInt();

    remoteServer = QHostAddress(
                getConfigurationParameter("serverAddress", "127.0.0.1")
                    .toString());
}

void SENDLOG::stop()
{
}
