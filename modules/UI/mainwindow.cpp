#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QScreen>
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QScrollBar>

#include <qdatetime.h>
#include "bus.h"
#include "guiwindowgraphicsobject.h"
#include <sstream>
#include <QResource>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QResource::registerResource("ui.rcc");
    setFocusPolicy(Qt::StrongFocus);

    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    scene = new QGraphicsScene(QRect(0, 0, 680, 100));
    ui->graphicsView->setScene(scene);

    Bus *leftBus = new Bus;
    leftBus->setImage(":/images/night next bus top.png");
    leftBus->setLabel("M285OM");
    leftBus->setTime("07:28");

    Bus *rightBus = new Bus;
    rightBus->setImage(":/images/night prev bus top.png");
    rightBus->setLabel("Y210OY");
    rightBus->setTime("02:58");

    GuiWindowGraphicsObject *object = new GuiWindowGraphicsObject(NULL, leftBus, rightBus);
    ui->graphicsView->scene()->addItem(object);
}

MainWindow::~MainWindow()
{
    delete ui;
}

