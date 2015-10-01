#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDir>
#include "dispatcher.h"

void enableSignalHandling();

void loadConfig(Dispatcher *, QString config = "");


int main(int argc, char *argv[])
{
    enableSignalHandling();

    QApplication app(argc, argv);

    Dispatcher *dispatcher = new Dispatcher();

    if(app.arguments().size() == 2) {
        loadConfig(dispatcher, app.arguments()[1]);
    } else {
        loadConfig(dispatcher);
    }

    dispatcher->startAll();

    return app.exec();
}

void loadConfig(Dispatcher * dispatcher, QString config) {
    if (QFile::exists(config)) {
        dispatcher->initializeAll(config);
    } else {
        qDebug() << "here";
        QStringList c;
        c << "[modules]" << "ui_instance=UI" << "test_instance=test_module";
        dispatcher->initializeAll(c);
    }
}
