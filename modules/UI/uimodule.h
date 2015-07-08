#ifndef UIMODULE_H
#define UIMODULE_H

#include <QObject>
#include <QLoggingCategory>
#include <QDebug>

#include "module.h"
#include "currentbus.h"

Q_DECLARE_LOGGING_CATEGORY(UI_MODULE)

class UIModule : public Module
{
    Q_OBJECT
    public:
        UIModule(QObject *parent = 0);
        ~UIModule() {}
        void start();
        void stop();
        QStringList getPubTopics();
        void respond(QString topic, ::indigo::pb::internal_msg &message);
        Q_SIGNAL void messageReceivedSignal(Bus*, Bus*, CurrentBus*);
};

#endif // UIMODULE_H
