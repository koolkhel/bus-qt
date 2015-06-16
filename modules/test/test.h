#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(TESTC)

class TestModule : public Module {
	Q_OBJECT

public:
    TestModule(QObject *parent = 0);
    ~TestModule() {};

    virtual void start();
    virtual void stop();

    virtual QStringList getPubTopics();

    QString getName() const;
public slots:
    virtual void respond(::indigo::pb::internal_msg &message);
};

#endif // TEST_H
