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

private slots:
    void read();
private:
    QUdpSocket *socket;

    int logPort;
};

#endif // SKEL_H
