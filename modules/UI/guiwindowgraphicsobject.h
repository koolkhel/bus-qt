#ifndef GUIWINDOWGRAPHICSOBJECT_H
#define GUIWINDOWGRAPHICSOBJECT_H
#include <QGraphicsObject>
#include "bus.h"
#include "currentbus.h"

class GuiWindowGraphicsObject: public QGraphicsObject
{
    Q_OBJECT

    public:
        GuiWindowGraphicsObject(Bus *previous =0, Bus *next =0,CurrentBus *me = 0);
        virtual ~GuiWindowGraphicsObject();
        QRectF boundingRect() const Q_DECL_OVERRIDE;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

    private:
        Bus *leftBus;
        Bus *rightBus;
        QString previousStationTime;
        QString currentRouteTime;
        QString nextStationTimeTable;
        QString nextStationForecasting;
};

#endif // GUIWINDOWGRAPHICSOBJECT_H
