#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>

#include "ui_message.pb.h"

#include "category.h"

#include "bus.h"
#include "guiwindowgraphicsobject.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    public slots:
        void update(const indigo::pb::schedule_movement_update &);
        void update(const ::indigo::pb::route_info &);
    private:
        void initializeStaticObjects();
        void initializeClocks();
        void initializeBus();
        void keyPressEvent(QKeyEvent * event);
        void timerEvent(QTimerEvent *);
     private:
        Ui::MainWindow *ui;

        QGraphicsScene *scene;

        QGraphicsTextItem * clocks[4];

        QGraphicsPixmapItem *Marker;

        Bus  *leftBus, *rightBus;

        GuiWindowGraphicsObject * Line;
        bool state;
        indigo::pb::route_info  RouteInfo;
        int id_timer;
};


#endif // MAINWINDOW_H
