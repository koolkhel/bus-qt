#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QTime>
#include <QString>
#include <QtGlobal>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(DEBOUNCEC)

class DEBOUNCE : public Module
{
    Q_OBJECT
public:
    DEBOUNCE(QObject *parent = 0);
    virtual ~DEBOUNCE();
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);

private:
    char bounceCounter;

    QTime timer;
    QString LimitTopic;
    QString id;
};

#endif // SKEL_H
