#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(BLACKBOXC)

class BLACKBOX : public Module
{
	Q_OBJECT

public:
    BLACKBOX(QObject *parent = 0);
    virtual ~BLACKBOX();
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);
};

#endif // SKEL_H
