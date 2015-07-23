#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(SENDLOGC)

class SENDLOG : public Module
{
	Q_OBJECT

public:
    SENDLOG(QObject *parent = 0);
    virtual ~SENDLOG();
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);


    void startServer();
    void stopServer();
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
};

#endif // SKEL_H
