#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(LOGSC)

class QUdpSocket;
class QTcpServer;
class QTcpSocket;

class LOGS : public Module
{
    Q_OBJECT

public:
    LOGS(QObject *parent = 0);
    virtual ~LOGS();

    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);

    void startServer();
    void stopServer();

    void log(QString &str);
public slots:
    void start();
    void stop();
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

    int logPort;
    bool do_console;
};

#endif // SKEL_H
