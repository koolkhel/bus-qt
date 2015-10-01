#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include "remoteprocess.h"

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(VPNREMOTEC)

class VPNREMOTE : public Module
{
	Q_OBJECT

public:
    VPNREMOTE(QObject *parent = 0);
    virtual ~VPNREMOTE();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);
public slots:
    void start();
    void stop();
private:
    RemoteProcess telnetd, openvpn;

};

#endif // SKEL_H
