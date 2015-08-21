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
#include "guiwindowgraphicsobject.h"

#include <QFontDatabase>
#include "timer.h"

const int staticBlockY = -195;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QResource::registerResource("../modules/UI/ui.rcc");
    QFontDatabase::addApplicationFont("DroidSans.ttf");

    ui->setupUi(this);

    setFocusPolicy(Qt::NoFocus);

    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    scene = new QGraphicsScene(QRect(0, 0, 680, 100));

    ui->graphicsView->setScene(scene);

    Line = new GuiWindowGraphicsObject();

    scene->addItem(Line);

    initializeStaticObjects();
    initializeClocks();
    initializeBus();

    state = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(const indigo::pb::schedule_movement_update &msg)
{
    if(!state) {
        qWarning () << "NOT INITIALIZED ROUTE";
        return;
    }
    ::indigo::pb::bus_on_route bus ;
    int i = 0;

    for(i = 0; i < msg.buses_size(); ++i) {
        if(RouteInfo.bus_number().compare(msg.buses(i).busname()) == 0) {
            bus = msg.buses(i);
            break;
        }
    }

    if(i == msg.buses_size()) {
        qWarning() << "cant find myself on route";
        return;
    }

    for(i = 0; i < msg.buses_size(); ++i) {
        if(msg.buses(i).route_order() == (bus.route_order() - 1)){
            leftBus->update(bus.time_to_prev(),msg.buses(i).busname());
        }
        if(msg.buses(i).route_order() == (bus.route_order() + 1)) {
            rightBus->update(bus.time_to_prev(),msg.buses(i).busname());
        }
    }
    if(bus.route_order() == 1) {
        leftBus->hide();
    } else {
        leftBus->show();
    }
    if(bus.route_order() ==( msg.buses_size() - 1)) {
        rightBus->hide();
    } else {
        rightBus->show();
    }

    Line->updatePoints(msg, bus.route_order());
    if(bus.seconds_from_route_start()) {  //Эпичный костылько,
                                                                       //решение одно, если сервер будет обычно слать 0, а когда машина выходит 1 секунду
                                                                       //Или каждые часы выделить в отдельные элементы,
                                                                       //но это не решит проблемы постоянно перерисовки
        static_cast < Timer * > (clocks[1])->changeTime(bus.seconds_from_route_start()*1000);
    }
    int time = msg.this_bus().previous_station_visit_time()*1000;
    if(time != 0) {
        if(time < 0) {
            clocks[0]->setPlainText(QString("-%1")
                                                        .arg(QTime::fromMSecsSinceStartOfDay(time).toString("mm:ss")));
        } else {
            clocks[0]->setPlainText(QTime::fromMSecsSinceStartOfDay(time).toString("mm:ss"));
        }
    }
    double position = bus.position() + 1; //special trunc
    qDebug() << position << RouteInfo.station_size();
    qDebug() << RouteInfo.station(position).schedule_times_size();
    clocks[3]->setPlainText(
                QTime::fromMSecsSinceStartOfDay(
                    RouteInfo.station(position).schedule_times(0).visit_time() * 1000)
                .toString("mm:ss"));
    ;
    Line->setPos(202.5 - bus.position() * Line->moveWidth() , 70);

}

void MainWindow::update(const indigo::pb::route_info &msg)
{

    RouteInfo = msg;
    state = true;
    QGraphicsTextItem * label = new QGraphicsTextItem(QString::fromStdString(RouteInfo.bus_number()));
    scene->addItem(label);
    label->setFont(QFont("Arial", 23));
    label->setDefaultTextColor(Qt::white);
    label->setPos(170, 0);

    Line->setRoute(&RouteInfo);
    Line->setPos(202.5, 70);
}

void MainWindow::initializeStaticObjects()
{
    int l_x[] = {170, -55, 460};
    int l_y[] = {40, staticBlockY, staticBlockY};
    QImage l_image[] = {QImage(":/images/night our marker.png"),
                                        QImage(":/images/night top static block.png"),
                                        QImage(":/images/night right static block.png")};
    for(int i = 0; i < 3; ++i) {
     QGraphicsPixmapItem * graphItem =
            new QGraphicsPixmapItem ((QPixmap::fromImage(l_image[i])));
        scene->addItem(graphItem);
        graphItem->setPos(l_x[i],l_y[i]);
    }
}

void MainWindow::initializeClocks()
{
    Timer * item = new Timer();
    item->setFont(QFont("DroidSans.ttf",22, QFont::Bold));
    ui->graphicsView->scene()->addItem(item);
    item->setPos(530, -125);

    for(int i = 0; i < 4; ++i) {      
        if(i == 1) {
            clocks[i] = new Timer(0);
        } else {
            clocks[i] = new QGraphicsTextItem();
        }
        clocks[i]->setDefaultTextColor(Qt::gray);
        clocks[i]->setPlainText("N/A");
        clocks[i]->setFont(QFont("DroidSans.ttf",22, QFont::Bold));
        ui->graphicsView->scene()->addItem(clocks[i]);
        clocks[i]->setPos(550, -20 + 80*i);
    }
}

void MainWindow::initializeBus()
{
    leftBus = new Bus(
                           Qt::red,
                           QPixmap::fromImage(QImage(":/images/night prev bus top.png")),
                           QPoint(12, staticBlockY+30));

    scene->addItem(leftBus->image());
    scene->addItem(leftBus->name());
    scene->addItem(leftBus->time());

    rightBus = new Bus(
                            Qt::green,
                            QPixmap::fromImage(QImage(":/images/night next bus top.png")),
                            QPoint(355, staticBlockY+30));

    scene->addItem(rightBus->image());
    scene->addItem(rightBus->name());
    scene->addItem(rightBus->time());
}
