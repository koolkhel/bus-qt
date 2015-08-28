#include "indigologger.h"

#include <QByteArray>
#include <QDebug>
#include <QDateTime>

#include <QThread>
#include <QMutex>

#include <QTimer>
#include <QEventLoop>

#include <QtNetwork/QTcpSocket>

Q_LOGGING_CATEGORY(GSM, "indigo.gsm")
Q_LOGGING_CATEGORY(ZMQ, "indigo.zmq")
Q_LOGGING_CATEGORY(GPS, "indigo.gps")
Q_LOGGING_CATEGORY(LOG, "indigo.log")

IndigoLogger *instance;

const QString logPattern = QString("%{time yyyy.MM.dd h:mm:ss.zzz} %{appname}: %{type} %{category} t:%{threadid} -- %{file}:%{line} -- %{message} %{if-fatal}%{backtrace depth=10}%{endif}\n");

void indigoLoggerStop()
{
    instance->stopServer();
}

void indigoLoggerStart()
{
    if (instance == NULL) {
        instance = new IndigoLogger();
        qSetMessagePattern(logPattern);
    }
    instance->startServer();
}

void indigoMessageHandler(QtMsgType type,
   const QMessageLogContext &context,
   const QString &message)
{
    static QMutex mutex;
    QMutexLocker lock(&mutex);
    if (instance == NULL) {
        instance = new IndigoLogger();
        qSetMessagePattern(logPattern);
    }

    QString logString = qFormatLogMessage(type,
                                          context, message);
    if (instance) {
        instance->log(logString);
    }

    //fprintf(stderr, "using log format %s", qPrintable(logPattern));
}

IndigoLogger::IndigoLogger()
{
    socket = new QUdpSocket();

    confServer = new QTcpServer();
    QObject::connect(confServer, SIGNAL(newConnection()), SLOT(acceptConfiguration()));
    startServer();
}

void IndigoLogger::startServer()
{
    if (!confServer->listen(QHostAddress::Any, CONF_PORT)) {
        fprintf(stderr, "no start server\n");
    }
}

void IndigoLogger::stopServer()
{
    confServer->close();
}

void IndigoLogger::acceptConfiguration()
{
    qCDebug(LOG) << "server: accept configuration client";
    confServer->pauseAccepting();
    while (confServer->hasPendingConnections()) {
        confClientSocket = confServer->nextPendingConnection();
        QObject::connect(confClientSocket, SIGNAL(readyRead()), SLOT(configurationDataReceived()));
        QObject::connect(confClientSocket, SIGNAL(disconnected()), SLOT(configurationClientDisconnected()));
    }
}

void IndigoLogger::configurationDataReceived()
{
    QString data = QString::fromLocal8Bit(confClientSocket->readLine());
    qCDebug(LOG) << "server: configuration received: " << data;
    QLoggingCategory::setFilterRules(data.simplified());
    emit configurationChanged();
}

void IndigoLogger::configurationClientDisconnected()
{
    qCDebug(LOG) << "server: client disconnected";
    if (confServer != NULL) {
        // FIXME сокет вылетает
        //confServer->resumeAccepting();
    }
    QObject::connect(confClientSocket, 0, 0);
    confClientSocket->deleteLater();
    confClientSocket = NULL;
}

void IndigoLogger::log(QString str)
{
    QByteArray qba = str.toLocal8Bit();

    socket->writeDatagram(qba.data(), qba.size(), QHostAddress::Broadcast, IndigoLogger::PORT);
}
