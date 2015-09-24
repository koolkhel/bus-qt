#ifndef SKEL_H
#define SKEL_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

#include "module.h"
#include <QSqlDatabase>

Q_DECLARE_LOGGING_CATEGORY(BLACKBOXC)

class QTimer;

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

private slots:
    void doBlackboxJob();

private:
    QSqlDatabase db;

    void initializeDB();
    void executeDDL(QString queryText);
    void copyFromRAMtoNAND();
    void store(int id, QByteArray data);
    void handleConfirmedMessages(::indigo::pb::internal_msg &message);

    void collectStatistics();

    int _ramRecordCount;
    int _nandRecordCount;
    int _sentRecordCount;
    int _confirmedRecordCount;

    QTimer *bbTimer;

    QString confirmedMessagesTopic;
};

#endif // SKEL_H
