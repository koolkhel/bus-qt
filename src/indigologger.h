#ifndef INDIGOLOGGER_H
#define INDIGOLOGGER_H

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpServer>
#include <QLoggingCategory>
#include <QDebug>

Q_DECLARE_LOGGING_CATEGORY(GPS)
Q_DECLARE_LOGGING_CATEGORY(GSM)
Q_DECLARE_LOGGING_CATEGORY(ZMQ)
Q_DECLARE_LOGGING_CATEGORY(LOG)

class IndigoLogger;

extern IndigoLogger *instance;

void indigoMessageHandler(QtMsgType type,
   const QMessageLogContext &context,
   const QString &message);


class IndigoLogger : public QObject
{
    Q_OBJECT
public:
    enum Config {
        PORT = 45000,
        CONF_PORT = 45001
    };

    IndigoLogger();
    virtual ~IndigoLogger() {}

    static IndigoLogger *getInstance() {
        if (instance == NULL)
            instance = new IndigoLogger();
        return instance;
    }

    void log(QString str);

signals:
    void configurationChanged();
private slots:
    void acceptConfiguration();
    void configurationDataReceived();
    void configurationClientDisconnected();

private:
    QUdpSocket *socket;
    QTcpServer *confServer;
    QTcpSocket *confClientSocket;
};

#endif // INDIGOLOGGER_H
