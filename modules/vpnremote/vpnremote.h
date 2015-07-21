#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QProcess>
#include <QVector>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(VPNREMOTEC)

class VPNREMOTE : public Module
{
	Q_OBJECT

public:
    VPNREMOTE(QObject *parent = 0);
    virtual ~VPNREMOTE();
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);
private:

    struct {
        QString path;
        QStringList StartParams;
        QStringList StopParams;
        bool state;
        QProcess process;
        bool start() {
            if(!state) {
                process.start(path, StartParams);
            }
            state = true;
        }
        bool stop() {
            if(state) {
                process.start(path, StopParams);
            }
            state = false;
        }
    }telnetd, openvpn;

};

#endif // SKEL_H
