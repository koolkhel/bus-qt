#include "bus.h"
#include <QFont>
#include <QTime>
#include <QGraphicsScene>

Bus::Bus(QColor fontColor, QPixmap l_Image, QPoint pos, QPoint eps) {
    m_image = new QGraphicsPixmapItem(l_Image);
    m_name = new QGraphicsTextItem();
    m_time =   new QGraphicsTextItem();

    m_time->setDefaultTextColor(fontColor);
    m_time->setFont(QFont("DroidSans.ttf",40, QFont::Bold));
    m_time->setPlainText("N/A");
    m_time->setPos(pos);

    m_image->setPos(pos.x() + eps.x(), pos.y() + eps.y());

    m_name->setDefaultTextColor(fontColor);
    m_name->setFont(QFont("DroidSans.ttf",18));
    m_name->setPlainText("N/A");
    m_name->setPos(pos.x()+ eps.x() - 15, pos.y() +  eps.y() + l_Image.height() + 10);
}

void Bus::init(QGraphicsScene *scene)
{
    if(scene == NULL)
        return;
    scene->addItem(m_image);
    scene->addItem(m_name);
    scene->addItem(m_time);
}

QGraphicsTextItem *Bus::name() const {
    return m_name;
}

QGraphicsTextItem *Bus::time() const {
    return m_time;
}

QGraphicsPixmapItem *Bus::image() const {
    return m_image;
}

void Bus::update(int time, const std::string &name) const {
    if(time == 0) {
        hide();
        return;
    }
    m_time->setPlainText(QTime::fromMSecsSinceStartOfDay(time).toString("mm:ss"));
    m_name->setPlainText(QString::fromStdString(name));
    show();
}

void Bus::show() const {
    m_image->show();
    m_name->show();
    m_time->show();
}

void Bus::hide() const {
    m_image->hide();
    m_name->hide();
    m_time->hide();
}

