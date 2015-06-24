#include "uimodule.h"
#include "mainwindow.h"

UiModule::UiModule(QObject *parent)
{
    this->name = "ui_instance";

}

UiModule::~UiModule() {}


void UiModule::start()
{
    QApplication a();
    MainWindow w;
    w.show();
}

void UiModule::stop()
{

}


QStringList UiModule::getPubTopics()
{
    QStringList topics;
    topics << "hello2";
    return topics;
}

QString UiModule::getName() const
{
    return name;
}

void UiModule::respond(indigo::pb::internal_msg &message)
{

}

