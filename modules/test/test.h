#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>
#include <QTimer>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(TESTC)

class TestModule : public Module
{
	Q_OBJECT
public:
    TestModule(QObject *parent = 0);
    virtual ~TestModule() {}
    virtual QStringList getPubTopics();

    // ----- test methods -------------
    void sendTestMessage();
    void sendMessage(::indigo::pb::internal_msg &msg, QString topic);
    void subscribeTopic(QString topic);

    Q_SIGNAL void messageReceivedSignal();

    // ----- end test methods --------

public slots:
    virtual void start();
    virtual void stop();

    void testBurstSlot();
    void testSlot();
    virtual void respond(QString topic, ::indigo::pb::internal_msg &message);
private:
    QTimer *testTimer;
    QString testTopic;
    int testMessageId;
};

#endif // TEST_H
