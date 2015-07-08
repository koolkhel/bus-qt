#include "logs.h"

#include <QMutex>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QLoggingCategory>
#include <QDebug>

Q_LOGGING_CATEGORY(LOGSC, "logs")

static LOGS *instance = NULL;
static const QString logPattern =
        QString("%{time yyyy.MM.dd h:mm:ss.zzz} %{appname}: %{type} %{category} t:%{threadid} -- %{file}:%{line} -- %{message} %{if-fatal}%{backtrace depth=10}%{endif}\n");

void indigoMessageHandler(QtMsgType type,
   const QMessageLogContext &context,
   const QString &message)
{
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if (instance == NULL)
        return;

    QString logString = qFormatLogMessage(type,
                                          context, message);
    instance->log(logString);

    //fprintf(stderr, "using log format %s", qPrintable(logPattern));
}

LOGS::LOGS(QObject *parent)
{
    setParent(parent);

    this->name = "logs works";
    logPort = 45000;
    do_console = false;

    qCDebug(LOGSC, "hello,world");

    instance = this;
}

LOGS::~LOGS()
{

}

QStringList LOGS::getPubTopics()
{
    QStringList topics;

    return topics;
}

void LOGS::respond(QString topic, indigo::pb::internal_msg &message)
{
}

void LOGS::start()
{
    logPort = getConfigurationParameter("logPort", 45000).toInt();

    socket = new QUdpSocket();

    confServer = new QTcpServer();
    QObject::connect(confServer, SIGNAL(newConnection()), SLOT(acceptConfiguration()));
    startServer();

    do_console = getConfigurationParameter("console", QVariant(false)).toBool();

    // применяем правила логгирования по модулю
    QMap<QString, QVariant> &configuration = getAllConfiguration();
    QString rules;
    foreach (QString key, configuration.keys()) {
        QString value = configuration.value(key).toString();
        if (value == "true" || value == "false") {
            QString rule = QString("%1=%2").arg(key).arg(value);
            fprintf(stderr, qPrintable(rule + "\n"));
            rules += rule + QStringLiteral("\n");
        }
    }

    QLoggingCategory::setFilterRules(rules);
    qSetMessagePattern(logPattern);
    qInstallMessageHandler(indigoMessageHandler);
}

void LOGS::stop()
{
    qInstallMessageHandler(0);
}


void LOGS::acceptConfiguration()
{
    qCDebug(LOGSC) << "server: accept configuration client";
    confServer->pauseAccepting();
    while (confServer->hasPendingConnections()) {
        confClientSocket = confServer->nextPendingConnection();
        QObject::connect(confClientSocket, SIGNAL(readyRead()), SLOT(configurationDataReceived()));
        QObject::connect(confClientSocket, SIGNAL(disconnected()), SLOT(configurationClientDisconnected()));
    }
}

void LOGS::configurationDataReceived()
{
    QString data = QString::fromLocal8Bit(confClientSocket->readLine());
    qCDebug(LOGSC) << "server: configuration received: " << data;
    QLoggingCategory::setFilterRules(data.simplified());
    emit configurationChanged();
}

void LOGS::configurationClientDisconnected()
{
    qCDebug(LOGSC) << "server: client disconnected";
    if (confServer != NULL) {
        // FIXME сокет вылетает
        //confServer->resumeAccepting();
    }
    QObject::connect(confClientSocket, 0, 0);
    confClientSocket->deleteLater();
    confClientSocket = NULL;
}

void LOGS::startServer()
{
    if (!confServer->listen(QHostAddress::Any, getConfigurationParameter("configurationServerPort", 45001).toInt())) {
        fprintf(stderr, "no start server\n");
    }
}

void LOGS::stopServer()
{
    confServer->close();
}

void LOGS::log(QString& str)
{
    QByteArray qba = str.toLocal8Bit();

    socket->writeDatagram(qba.data(), qba.size(), QHostAddress::Broadcast, logPort);

    if (do_console) {
        fprintf(stderr, qPrintable(str));
    }
}
