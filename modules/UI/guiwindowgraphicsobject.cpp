#include "guiwindowgraphicsobject.h"
#include "bus.h"
#include "currentbus.h"
#include <QPainter>
#include <QTextOption>
#include <QTime>

GuiWindowGraphicsObject::GuiWindowGraphicsObject(Bus *previous, Bus *next, CurrentBus *me)
{
    leftBus = previous;
    rightBus = next;
    previousStationTime = me->getPreviousStationTime();
    currentRouteTime = me->getCurrentRouteTime();
    nextStationTimeTable = me->getNextStationTimeTable();
    nextStationForecasting = me->getNextStationForecasting();
}

GuiWindowGraphicsObject::~GuiWindowGraphicsObject()
{

}

QRectF GuiWindowGraphicsObject::boundingRect() const
{
    return QRectF(0, 0, 200, 200);
}

void GuiWindowGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setFont(QFont("Times",22, QFont::Bold));

    const int leftBusLeft = 10;
    const int leftBusTop = -135;
    const int rightBusLeft = 355;
    const int widthText = 200;
    const int heightText = 100;
    const int rightBlockLevel = 570;

    QImage currMarker(":/images/night our marker.png");
    painter->setRenderHint(QPainter::Antialiasing);

    //Статичные картинки
    painter->drawImage(-55, -215,QImage(":/images/night top static block.png"));
    painter->drawImage(470, -215, QImage(":/images/night right static block.png"));

    //Левый автобус
    painter->setPen(QPen(Qt::red, 1));
    painter->drawImage(leftBusLeft,leftBusTop,QImage(leftBus->getImage()));

    painter->drawText(QRectF(leftBusLeft,-185,widthText, heightText),leftBus->getTime());
    painter->drawText(QRectF(leftBusLeft,-115,widthText, heightText),leftBus->getLabel());

    //Правый автобус
    painter->setPen(QPen(Qt::green,1));
    painter->drawImage(rightBusLeft, leftBusTop,QImage(rightBus->getImage()));
    painter->drawText(QRect(rightBusLeft, -185,widthText,heightText),rightBus->getTime());
    painter->drawText(QRect(rightBusLeft, -115,widthText,heightText),rightBus->getLabel());
    painter->setPen(QPen(Qt::gray,1));

    QTime time = QTime::currentTime();
    painter->drawText(QRect(rightBlockLevel - 20,leftBusTop - 10,widthText,heightText),time.toString());
    painter->drawText(QRect(rightBlockLevel,-40,widthText,heightText), previousStationTime);
    painter->drawText(QRect(rightBlockLevel,40,widthText,heightText), currentRouteTime);
    painter->drawText(QRect(rightBlockLevel,120,widthText,heightText),nextStationTimeTable);
    painter->drawText(QRect(rightBlockLevel,200,widthText,heightText),nextStationForecasting);
    painter->drawImage(leftBusLeft - 30, 70,currMarker);

    for(int i=0; i< 2; i++)
    {
        painter->drawImage(leftBusLeft + 200 *i , 180,QImage(":/images/station1-black.png"));
        painter->drawImage(leftBusLeft + 30 + 200*i ,192,QImage(":/images/section12-black.png"));
        painter->drawText(leftBusLeft + 200 *i, 240,"Некрасовский");
    }
}



