#include "logs.h"

#include <QMutex>
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

void LOGS::log(QString& str)
{
    if (do_console) {
        fprintf(stderr, qPrintable(str));
    }
}
