#include "uimodule.h"
#include "mainwindow.h"

UiModule::UiModule(QObject *parent)
{

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

