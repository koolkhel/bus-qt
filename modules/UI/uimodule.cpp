#include "uimodule.h"
#include "skel_message.pb.h"
#include "test_message.pb.h"
#include "mainwindow.h"
#include "ui_message.pb.h"
#include "currentbus.h"

#include <QApplication>


Q_LOGGING_CATEGORY(UIMODULE, "UI")


UIModule::UIModule(QObject *parent)
{
    //setParent(parent);
    this->name = "ui_instance";
    qCDebug(UIMODULE, "hello,world");
}

void UIModule::start()
{
    MainWindow w;
    w.show();
    subscribe("test_instance");
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
    ::indigo::pb::ui_message msg = message.GetExtension(::indigo::pb::ui_message::ui_message_in);
    Bus *leftBus = new Bus(QString::fromStdString(msg.previousbustime()),QString::fromStdString(msg.previousbuslabel()),QString::fromStdString(msg.previousbusimage()));
    Bus *rightBus = new Bus(QString::fromStdString(msg.secondbustime()),QString::fromStdString(msg.secondbuslabel()),QString::fromStdString(msg.secondbusimage()));
    CurrentBus *currentBus = new CurrentBus(QString::fromStdString(msg.currentroutetime()), QString::fromStdString(msg.previousstationtime()), QString::fromStdString(msg.nextstationtimetable()), QString::fromStdString(msg.nextstationforecasting()));
    emit messageReceivedSignal(leftBus,rightBus,currentBus);
}
