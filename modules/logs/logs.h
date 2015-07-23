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
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);

    void log(QString &str);
private:

    bool do_console;
};

#endif // SKEL_H
