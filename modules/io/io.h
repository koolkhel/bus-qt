#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QSharedPointer>
#include "resource.h"
#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(IOC)

class IO : public Module
{
	Q_OBJECT

public:
    IO(QObject *parent = 0);
    virtual ~IO();
    void start();
    void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);
public slots:
    void doOutputJob();
    void doInputJob(uint64_t content);
private:
    QVector < QSharedPointer < Resource > > resources;
    QTimer timer;
    uint64_t oldState;
};

#endif // SKEL_H
