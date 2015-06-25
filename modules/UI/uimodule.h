#ifndef UIMODULE_H
#define UIMODULE_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

#include "module.h"

Q_DECLARE_LOGGING_CATEGORY(UI_MODULE)

class UIModule :public Module
{
    Q_OBJECT
public:
    UIModule(QObject *parent = 0);
    virtual ~UIModule() {}
    virtual void start();
    virtual void stop();
    virtual QStringList getPubTopics();
    virtual void respond(QString topic, ::indigo::pb::internal_msg &message);

    void show();
    void getElements();

    void sendTestMessage();
    void subscribeTopic(QString topic);

    Q_SIGNAL void messageReceivedSignal();
};

#endif // UIMODULE_H
