#include "uimodule.h"
#include "mainwindow.h"

UiModule::UiModule(QObject *parent)
{
    this->name = "ui_instance";

}

UiModule::~UiModule()
{

}

void UiModule::start()
{

}

void UiModule::stop()
{

}

void UiModule::show()
{
    MainWindow w;
    w.show();
}

