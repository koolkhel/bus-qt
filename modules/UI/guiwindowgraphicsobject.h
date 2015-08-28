#ifndef GUIWINDOWGRAPHICSOBJECT_H
#define GUIWINDOWGRAPHICSOBJECT_H
#include <QGraphicsObject>
#include <QVector>

#include "ui_message.pb.h"

#include "category.h"
class GuiWindowGraphicsObject: public QGraphicsObject
{
    Q_OBJECT

    public:
        GuiWindowGraphicsObject();
        virtual ~GuiWindowGraphicsObject();
        QRectF boundingRect() const Q_DECL_OVERRIDE;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
        void updatePoints(const indigo::pb::schedule_movement_update &info, int me);
        void setRoute(const indigo::pb::route_info *);
        int moveWidth();
    private:
        const indigo::pb::route_info * RouteInfo;
        indigo::pb::schedule_movement_update BusInfo;
        int m_me;
        int mvWidth;
};

#endif // GUIWINDOWGRAPHICSOBJECT_H
