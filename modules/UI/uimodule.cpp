#include "uimodule.h"
#include "mainwindow.h"

UiModule::UiModule(QObject *parent)
{
    this->name = "ui_instance";

}


void UiModule::start()
{
    QApplication a();
    MainWindow w;
    w.show();
}

void UiModule::stop()
{

}

void UiModule::show()
{
    MainWindow w;
    w.show();
}

QStringList UiModule::getPubTopics()
{
    QStringList topics;
    topics << "hello2";
}

void UiModule::respond(indigo::pb::internal_msg &message)
{

}

