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

void SENDLOG::startServer()
{
    if (!confServer->listen(QHostAddress::Any, getConfigurationParameter("configurationServerPort", 45001).toInt())) {
        fprintf(stderr, "no start server\n");
    }
}

void SENDLOG::stopServer()
{
        confServer->close();
}

void SENDLOG::acceptConfiguration()
{
    qCDebug(SENDLOGC) << "server: accept configuration client";
    confServer->pauseAccepting();
    while (confServer->hasPendingConnections()) {
        confClientSocket = confServer->nextPendingConnection();
        QObject::connect(confClientSocket, SIGNAL(readyRead()), SLOT(configurationDataReceived()));
        QObject::connect(confClientSocket, SIGNAL(disconnected()), SLOT(configurationClientDisconnected()));
    }
}

void SENDLOG::configurationDataReceived()
{
    QString data = QString::fromLocal8Bit(confClientSocket->readLine());
    qCDebug(SENDLOGC) << "server: configuration received: " << data;
    QLoggingCategory::setFilterRules(data.simplified());
    emit configurationChanged();
}

void SENDLOG::configurationClientDisconnected()
{
    qCDebug(SENDLOGC) << "server: client disconnected";
    if (confServer != NULL) {
        // FIXME сокет вылетает
        //confServer->resumeAccepting();
    }
    QObject::connect(confClientSocket, 0, 0);
    confClientSocket->deleteLater();
    confClientSocket = NULL;
}

void SENDLOG::start()
{
    logPort = getConfigurationParameter("logPort", 45000).toInt();

    socket = new QUdpSocket();

    confServer = new QTcpServer();
    QObject::connect(confServer, SIGNAL(newConnection()), SLOT(acceptConfiguration()));
    startServer();
}

void SENDLOG::stop()
{
}
