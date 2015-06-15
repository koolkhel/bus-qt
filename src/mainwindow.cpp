#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "indigo_message.pb.h"

#include <QDebug>
#include <QScreen>
#include <QDesktopWidget>
#include <QGraphicsPixmapItem>
#include <QScrollBar>

#include <qdatetime.h>
#include "socket.h"
#include "zeromqpublisher.h"
#include "zeromqsubscriber.h"
#include <zmq.hpp>
#include <sstream>

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    backend(NULL)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);

    backend = new Backend(this);

    connect(backend, SIGNAL(newSatellitesUsed(int)), SLOT(satellitesInUseUpdated(int)));

    int _dpi = 170;
    QScreen *screen = QApplication::screens().at(0);
    int _width = qMin(screen->size().width(), 800);
    int _height = qMin(screen->size().height(), 480);
    qDebug() << "screen width " << _width << " height " << _height;

    _dpi = (int) sqrt(_width*_width + _height*_height) / 5; // average screen size
    qDebug() << "calculated DPI:" << _dpi;
    setDPI(_dpi);

    backend->reconnect();

    pict = new QGraphicsPixmapItem();

    QPixmap image(":/images/us-marker.png");
    pict->setPixmap(image);
    pict->setX(0);
    pict->setY(0);

    connect(this, SIGNAL(usXChanged(int)), SLOT(usUpdate()));

    scene = new QGraphicsScene(QRect(0, 0, 800, 480));
    ui->graphicsView->setScene(scene);

    scene->addItem(pict);

    //ui->graphicsView->horizontalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    //ui->graphicsView->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");

    ui->graphicsView->move(0, 0);
    ui->graphicsView->ensureVisible(pict);

    QPropertyAnimation *anim = new QPropertyAnimation(this, "usX");
    anim->setStartValue(0);
    anim->setEasingCurve(QEasingCurve::InElastic);
    anim->setEndValue(800);
    anim->setDuration(5000);

    QPropertyAnimation *anim_2 = new QPropertyAnimation(this, "usX");
    anim_2->setEasingCurve(QEasingCurve::InOutBounce);
    anim_2->setEndValue(0);
    anim_2->setDuration(2000);

    connect(anim, SIGNAL(finished()), anim_2, SLOT(start()));
    connect(anim_2, SIGNAL(finished()), anim, SLOT(start()));

    anim->start();
}

void MainWindow::usUpdate()
{
    pict->setY(0);
    pict->setX(m_usX);
    //ui->graphicsView->ensureVisible(pict);
    ui->graphicsView->centerOn(pict);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDPI(int _dpi)
{
    setProperty("_q_customDpiX", QVariant(_dpi));
    setProperty("_q_customDpiY", QVariant(_dpi));
}

void MainWindow::buttonClicked()
{
    pict->setX(pict->x() + 1);
}

void MainWindow::timeUpdate()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString text = dateTime.time().toString("hh:mm:ss");
    ui->label->setText(text);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "key pressed: " << event->text();
    switch (event->key()) {
    case Qt::Key_Enter:
        qDebug() << "enter";
        break;
    case Qt::Key_Escape:
        qDebug() << "escape";
        break;
    case Qt::Key_Up:
        qDebug() << "key up";
        break;
    case Qt::Key_Down:
        qDebug() << "key down";
        break;
    case Qt::Key_Left:
        qDebug() << "key left";
        break;
    case Qt::Key_Right:
        qDebug() << "key right";
        break;

    }
}

// from gps
void MainWindow::positionUpdated(const QGeoPositionInfo &update)
{

}

void MainWindow::satellitesInUseUpdated(int count)
{
    ui->label->setText(QString("%1").arg(count));
}

void MainWindow::on_pushButton_2_clicked()
{
    /*QString filter = "GPS";
    ZeroMQPublisher *publisher = new ZeroMQPublisher("tcp://127.0.0.1:8080",filter);
    ZeroMQSubscriber *subscriber = new ZeroMQSubscriber();
    subscriber->subscribeTo("tcp://127.0.0.1:8080",filter);

    publisher->sendMessage("Hello");
*/
    /*Socket socket;
    socket.send("Hello");
    socket.run();*/

}
