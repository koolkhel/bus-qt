#include "guiwindowgraphicsobject.h"
#include <QPainter>
#include <QTextOption>
#include <QTime>
#include <QFontDatabase>
#include <QDebug>

GuiWindowGraphicsObject::GuiWindowGraphicsObject()
{
    RouteInfo = NULL;
}

GuiWindowGraphicsObject::~GuiWindowGraphicsObject()
{

}

QRectF GuiWindowGraphicsObject::boundingRect() const
{
    if(RouteInfo == NULL)
        return QRectF(0,0,0,0);

    return QRectF(-20, 0, 200*RouteInfo->station_size(), 150);
}

void GuiWindowGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(RouteInfo == NULL) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        return;
    }
    painter->setPen(QPen(Qt::white,1));

    painter->setRenderHint(QPainter::Antialiasing);

    QImage FirstStation(":/images/station1-black.png"),
                   LastStation(":/images/station1-black.png"),
                   RegularStation(":/images/station1-black.png"),
                   BlankLine(":/images/section12-black.png"),
                   NextBus(":/images/night next marker.png"),
                   PrevBus(":/images/night prev marker.png");

    const int y = qMax(PrevBus.height(), NextBus.height()) + 30;
    const int x = 0;
    mvWidth = BlankLine.width();
    const int lineEps    = qMax(RegularStation.height(), qMax(FirstStation.height(), LastStation.height())) / 2.5;

    for(int i = 0; i < BusInfo.buses_size(); ++i) {
        ::indigo::pb::bus_on_route bus = BusInfo.buses(i);
        if(bus.route_order() != m_me) {
                painter->drawText(
                                    x - bus.busname().length() * 1.3 + mvWidth*bus.position() ,
                                    0,
                                    QString::fromStdString(bus.busname()));
                painter->drawImage(
                            x + mvWidth * bus.position(),
                            30,
                            ((bus.route_order() < m_me)  ? PrevBus : NextBus));
        }
    }

    painter->drawImage(x , y,FirstStation);

    if(RouteInfo->station_size() > 1) {
        painter->drawImage(x ,y + lineEps,BlankLine);
        painter->drawImage(x + mvWidth*(RouteInfo->station_size()-1), y, LastStation);
    }
    for(int i=1; i< (RouteInfo->station_size() - 1); i++) {
        painter->drawImage(
                    x  + mvWidth *i ,
                    y,
                    RegularStation);
        painter->drawImage(x + lineEps + mvWidth*i ,y + lineEps,BlankLine);
    }
    for(int i = 0; i < RouteInfo->station_size(); ++i)  {
        const std::string *name = &RouteInfo->station(i).station_name();
        painter->drawText(x - name->length() * 1.3 + mvWidth *i,
                                          y + lineEps*3.5+ 20*(i & 1),
                          QString::fromStdString(*name));
    }
}

void GuiWindowGraphicsObject::updatePoints(const indigo::pb::schedule_movement_update &info, int me)
{
    BusInfo = info;
    m_me=me;
}

void GuiWindowGraphicsObject::setRoute(const indigo::pb::route_info *rte)
{
    RouteInfo = rte;
    if(RouteInfo->station_size() == 0) {
        qWarning() << "Something strange 0 Names";
    }
}

int GuiWindowGraphicsObject::moveWidth()
{
    return mvWidth;
}
