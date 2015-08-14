#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QtGlobal>

#include "module.h"
#include "indigo_message.pb.h"
#include "debounce_message.pb.h"
#include "io_message.pb.h"

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

    bool inputCheck(QString topic, indigo::pb::internal_msg &message);
 public slots:
    void stabilized();
private:
    indigo::pb::internal_msg dbcMessage;
    indigo::pb::debounce_message *dbc;
    int bounceCounter;
    int limitBounce;
    int timeout;
    QTimer bounceStarted;    
    int state ;
    QString LimitTopic;
    QString filtredTopic;
    ::indigo::pb::io_message_IO_id id;
};

#endif // SKEL_H
