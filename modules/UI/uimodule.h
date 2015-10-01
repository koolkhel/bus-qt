#ifndef UIMODULE_H
#define UIMODULE_H

#include <QObject>
#include <QDebug>

#include "module.h"

#include "ui_message.pb.h"

#include "mainwindow.h"
#include "category.h"


class UIModule : public Module
{
    Q_OBJECT
    public:
        UIModule(QObject *parent = 0);
        ~UIModule() {}

        QStringList getPubTopics();
        void respond(QString topic, ::indigo::pb::internal_msg &message);
public slots:
        void start();
        void stop();
private:
        MainWindow *w;
};

#endif // UIMODULE_H
