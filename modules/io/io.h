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
#include "io_message.pb.h"

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
    void doOutputJob(uint64_t content);
    void doInputJob();
private:
    Resource *resource;
    QString inputTopic;
    QString outputTopic;
    ::indigo::pb::io_message_IO_id id;
    QTimer timer;
};

#endif // SKEL_H
