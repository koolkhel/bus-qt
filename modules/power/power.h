#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QMap>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(POWERC)

class POWER : public Module
{
	Q_OBJECT

public:
    POWER(QObject *parent = 0);
    virtual ~POWER();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);
public slots:
    void start();
    void stop();
private:
    void doPowerJob();
private:
    int S1, S2, ACPG;
    QMap < int, int > privateID;
    QString  powerTopic;
};


#endif // SKEL_H
