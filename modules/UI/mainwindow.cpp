#include <QDebug>
#include <QScreen>
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QScrollBar>
#include <sstream>
#include <QResource>
#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bus.h"
#include "guiwindowgraphicsobject.h"
#include "currentbus.h"

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
    leftBus->setLabel("N/A");
    leftBus->setTime("N/A");

    Bus *rightBus = new Bus;
    rightBus->setImage(":/images/night prev bus top.png");
    rightBus->setLabel("N/A");
    rightBus->setTime("N/A");

    CurrentBus *me = new CurrentBus;
    me->setNextStationForecasting("N/A");
    me->setNextStationTimeTable("N/A");
    me->setPreviousStationTime("N/A");
    me->setCurrentRouteTime("N/A");

    GuiWindowGraphicsObject *object = new GuiWindowGraphicsObject (leftBus, rightBus, me);
    ui->graphicsView->scene()->addItem(object);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(Bus *prevBus, Bus *secBus,CurrentBus *me)
{
    scene = new QGraphicsScene(QRect(0, 0, 680, 100));
    ui->graphicsView->setScene(scene);

    GuiWindowGraphicsObject *object = new GuiWindowGraphicsObject(prevBus, secBus, me);
    ui->graphicsView->scene()->addItem(object);
}

