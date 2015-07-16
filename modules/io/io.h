#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QFile>
#include <QTimer>
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
    void publish(QByteArray);
private:

    QVector <QPair < Resource*, QTimer *> > data;
};

#endif // SKEL_H
