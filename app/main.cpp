#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QLabel>
#include <QDebug>

#include "testclass.h"

void enableSignalHandling();

int main(int argc, char *argv[])
{
    enableSignalHandling();
    QApplication a(argc, argv);

    //QResource::registerResource("/home/yury/work/QTFinal/indigo.qcc");
/*
    qApp->setStyle(QStyleFactory::create("Fusion"));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(15,15,15));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);

    palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(palette);
*/
    MainWindow w;
//    w.setPalette(palette);
    w.show();
    testclass cl;
    cl.test();

    return a.exec();
}
