#include <QScreen>
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QScrollBar>
#include <sstream>
#include <QResource>
#include <QDateTime>
#include <unistd.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "guiwindowgraphicsobject.h"

#include <QFontDatabase>
#include "timer.h"

const int staticBlockY = -190;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if(!QResource::registerResource("../modules/UI/ui.rcc")) {
        qCWarning(UIMODULE) << "Error Loading resouce file(NO IMAGES)";
        abort();
    }
    if(QFontDatabase::addApplicationFont("../modules/UI/fonts/DroidSans.ttf") == -1) {
        qCDebug(UIMODULE) << "Error Loading font";
        abort();
    }
    if(QFontDatabase::addApplicationFont("../modules/UI/fonts/DroidSans-Bold.ttf") == -1) {
        qCDebug(UIMODULE) << "Error Loading font";
        abort();
    }

    ui->setupUi(this);

    setFocusPolicy(Qt::NoFocus);

    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    scene = new QGraphicsScene(0, 0, 680, 100);

    ui->graphicsView->setScene(scene);

    Line = new GuiWindowGraphicsObject();

    scene->addItem(Line);

    initializeStaticObjects();
    initializeClocks();
    initializeBus();

    state = false;
    id_timer = 0;
    //this->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(const indigo::pb::schedule_movement_update &msg)
{
    if(!state) {
        qCWarning (UIMODULE) << "NOT INITIALIZED ROUTE";
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
        qCWarning(UIMODULE) << "cant find myself on route";
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
    if(bus.route_order() == msg.buses_size()) {
        rightBus->hide();
    } else {
        rightBus->show();
    }

    Line->updatePoints(msg, bus.route_order());
    if(bus.seconds_from_route_start()) {
        static_cast < Timer * > (clocks[1])->changeTime(bus.seconds_from_route_start()*1000);
    }
    int time = msg.this_bus().previous_station_visit_time()*1000;
    if(time != 0) {
        if(time < 0) {
            clocks[0]->setPlainText(QString("-%1")
                                                        .arg(QTime::fromMSecsSinceStartOfDay(-time).toString("mm:ss")));
        } else {
            clocks[0]->setPlainText(QTime::fromMSecsSinceStartOfDay(time).toString("mm:ss"));
        }
        if(time > -2*60*1000) {
            clocks[0]->setDefaultTextColor(Qt::green);
        } else {
            clocks[0]->setDefaultTextColor(Qt::red);
        }
    }

    clocks[3]->setPlainText(
                QTime::fromMSecsSinceStartOfDay(
                    RouteInfo.station(bus.position() + 1).schedule_times(0).visit_time() * 1000)
                .toString("mm:ss"));
    ;
    Line->setPos(202.5 - bus.position() * Line->moveWidth() , 70);
    qCDebug(UIMODULE) << "Update positions";
}

void MainWindow::update(const indigo::pb::route_info &msg)
{
    qCDebug(UIMODULE) << "Initialize route with "<< msg.station_size() << "stations";
    RouteInfo = msg;
    state = true;

    Line->setRoute(&RouteInfo);
    Line->setPos(202.5, 70);
}

void MainWindow::initializeStaticObjects()
{
    int l_x[] = {170, -58, 460};
    int l_y[] = {40, staticBlockY, staticBlockY};
    QImage l_image[] = {QImage(":/images/night our marker.png"),
                                        QImage(":/images/night top static block.png"),
                                        QImage(":/images/night right static block.png")};
    for(int i = 0; i < 3; ++i) {
     QGraphicsPixmapItem * graphItem =
            new QGraphicsPixmapItem ((QPixmap::fromImage(l_image[i])));
        scene->addItem(graphItem);
        graphItem->setPos(l_x[i],l_y[i]);

        if(i == 0) {
            Marker = graphItem;
        }
    }
}

void MainWindow::initializeClocks()
{
    Timer * item = new Timer();
    item->setFont(QFont("../modules/UI/fonts/DroidSans.ttf",45, QFont::Bold));
    ui->graphicsView->scene()->addItem(item);
    item->setPos(465, staticBlockY + 35);

    for(int i = 0; i < 4; ++i) {      
        if(i == 1) {
            clocks[i] = new Timer(0);
        } else {
            clocks[i] = new QGraphicsTextItem();
        }
        clocks[i]->setDefaultTextColor(Qt::white);
        clocks[i]->setPlainText("N/A");
        clocks[i]->setFont(QFont("../modules/UI/fonts/DroidSans.ttf",33));
        ui->graphicsView->scene()->addItem(clocks[i]);
        clocks[i]->setPos(530, staticBlockY+163 + 80*i);
    }
}

void MainWindow::initializeBus()
{
    leftBus = new Bus(
                           Qt::red,
                           QPixmap::fromImage(QImage(":/images/night prev bus top.png")),
                           QPoint(-20, staticBlockY+5),
                            QPoint(30, 75));
    leftBus->init(scene);

    rightBus = new Bus(
                            Qt::green,
                            QPixmap::fromImage(QImage(":/images/night next bus top.png")),
                            QPoint(270, staticBlockY+5),
                            QPoint(80, 75));
    rightBus->init(scene);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qCDebug(UIMODULE) << "key pressed: " << event->key();
    Marker->show();
    switch(event->key()) {
    case Qt::Key_Up: Marker->setPos(170, 0); break;
    case Qt::Key_Down: Marker->setPos(170, 80); break;
    case Qt::Key_Left: Marker->setPos(130, 40); break;
    case Qt::Key_Right: Marker->setPos(210, 40); break;
    default: Marker->hide(); break;
    }
    if(id_timer != 0) {
        killTimer(id_timer);
    }
    id_timer = startTimer(2000);
}

void MainWindow::timerEvent(QTimerEvent *timer)
{
    Marker->setPos(170, 40);
    Marker->show();
    killTimer(timer->timerId());
}
