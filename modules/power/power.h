#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QMap>
#include <QTimer>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(POWERC)

class POWER : public Module
{
	Q_OBJECT

public:
    POWER(QObject *parent = 0);
    virtual ~POWER();
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);
public slots:
    void doPowerJob();
private:
    QMap<QString, int> devices;
    int delayedStart;

    QTimer timer;
};

#endif // SKEL_H
