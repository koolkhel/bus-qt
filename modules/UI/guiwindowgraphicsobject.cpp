#include "guiwindowgraphicsobject.h"
#include <QPainter>
#include <QTextOption>

GuiWindowGraphicsObject::GuiWindowGraphicsObject()
{
    RouteInfo = NULL;
    mvWidth = 200;

    FirstStation = new QImage(":/images/night end station.png");
    LastStation = new QImage(":/images/night end station.png");
    RegularStation = new QImage(":/images/night middle station.png");
    BlankLine = new QImage(":/images/night section.png");
    NextBus = new QImage(":/images/night next marker.png");
    PrevBus = new QImage(":/images/night prev marker.png");
}

GuiWindowGraphicsObject::~GuiWindowGraphicsObject()
{

}

QRectF GuiWindowGraphicsObject::boundingRect() const
{
    if(RouteInfo == NULL)
        return QRectF(0,0,0,0);

    return QRectF(0, 0, mvWidth*(RouteInfo->station_size() + 1), 200);
}

void GuiWindowGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(RouteInfo == NULL) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        return;
    }
    painter->setFont(QFont("Droid Sans",16, QFont::Bold));
    painter->setPen(QPen(Qt::white,2));

    painter->setRenderHint(QPainter::Antialiasing);

    const int y = qMax(PrevBus->height(), NextBus->height()) + (painter->font().pointSize() * 2) + 5;
    const int x = 0;
    mvWidth = BlankLine->width() + FirstStation->width();
    const int lineEps    = qMax(RegularStation->height(), qMax(FirstStation->height(), LastStation->height())) / 2.5;

    for(int i = 0; i < BusInfo.buses_size(); ++i) {
        ::indigo::pb::bus_on_route bus = BusInfo.buses(i);
        if(bus.route_order() != m_me) {
                painter->drawText(
                                    x - bus.busname().length() * 1.3 + mvWidth*bus.position() ,
                                    (painter->font().pointSize() * 2),
                                    QString::fromStdString(bus.busname()));
                painter->drawImage(
                            x + mvWidth * bus.position(),
                            (painter->font().pointSize() * 2) + 5,
                            ((bus.route_order() < m_me)  ? *PrevBus : *NextBus));
        }
    }

    painter->drawImage(x , y, *FirstStation);

    if(RouteInfo->station_size() > 1) {
        painter->drawImage(x + FirstStation->width() ,y + lineEps, *BlankLine);
        painter->drawImage(x + mvWidth*(RouteInfo->station_size()-1), y, *LastStation);
    }
    for(int i=1; i< (RouteInfo->station_size() - 1); i++) {
        painter->drawImage(
                    x  + mvWidth *i ,
                    y,
                    *RegularStation);
        painter->drawImage(x  + mvWidth*i + FirstStation->width() ,y + lineEps, *BlankLine);
    }
    for(int i = 0; i < RouteInfo->station_size(); ++i)  {
        const std::string *name = &RouteInfo->station(i).station_name();
        painter->drawText(x + mvWidth *i,
                                          y + lineEps*3.5 + 10 + (painter->font().pointSize() + 7)*(i & 1),
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
        qCWarning(UIMODULE) << "Something strange 0 Names";
    }
}

int GuiWindowGraphicsObject::moveWidth()
{
    return mvWidth;
}
