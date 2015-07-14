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

    void setTimeout(qint64 timeout = 5 * 1000 * 1000);

private:
    typedef QPair<QTime, QString> Item;
    QList < Item > items;
    qint64 m_timeout;

    QString LimitTopic;
};

#endif // SKEL_H
