#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QVector>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(STOPSC)

class STOPS : public Module
{
	Q_OBJECT

public:
    STOPS(QObject *parent = 0);
    virtual ~STOPS();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, indigo::pb::internal_msg &message);
public slots:
    void start();
    void stop();
private:
    bool check(int sc);
    int typeOfLogic;
    int storedSteps;
    int accuracy;
    QString stopTopic;
    QVector < QPair<int, int> > steps;


};

#endif // SKEL_H
