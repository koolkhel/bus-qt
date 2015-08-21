#include "uimodule.h"
#include "skel_message.pb.h"
#include "test_message.pb.h"
#include "mainwindow.h"
#include "ui_message.pb.h"
#include <unistd.h>
#include <QApplication>


Q_LOGGING_CATEGORY(UIMODULE, "UI")


UIModule::UIModule(QObject *parent)
{
    setParent(parent);
    this->name = "ui_instance";
    qCDebug(UIMODULE, "hello,world");
}

void UIModule::start()
{
    w = new MainWindow();
    w->show();
    QString inputTopic= getConfigurationParameter("inputTopic", "ui_topic").toString();
    subscribe(inputTopic);

}

void UIModule::stop()
{

}

QStringList UIModule::getPubTopics()
{
    QStringList topics;
    topics << "uimodule_topic";
    return topics;
}

void UIModule::respond(QString topic, indigo::pb::internal_msg &message)
{
    Q_UNUSED(topic)
    if(message.HasExtension(::indigo::pb::route_info::route_info_in)) {
        qDebug() << "route_info_in";
        w->update(message.GetExtension(::indigo::pb::route_info::route_info_in));
    }
    if(message.HasExtension(indigo::pb::schedule_movement_update::schedule_update_in)) {
        qDebug() << "schedule_update_in";
        w->update(message.GetExtension(indigo::pb::schedule_movement_update::schedule_update_in));
    }
}


