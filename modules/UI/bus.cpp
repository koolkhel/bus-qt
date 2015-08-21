#include "bus.h"
#include <QFont>
#include <QTime>

Bus::Bus(QColor fontColor, QPixmap l_Image, QPoint pos) {
    m_image = new QGraphicsPixmapItem(l_Image);
    m_name = new QGraphicsTextItem();
    m_time =   new QGraphicsTextItem();

    m_name->setDefaultTextColor(fontColor);
    m_name->setFont(QFont("DroidSans.ttf",22, QFont::Bold));
    m_name->setPlainText("N/A");
    m_name->setPos(pos);

    m_image->setPos(pos.x(), pos.y() + 50);

    m_time->setDefaultTextColor(fontColor);
    m_time->setFont(QFont("DroidSans.ttf",22, QFont::Bold));
    m_time->setPlainText("N/A");
    m_time->setPos(pos.x(), pos.y() + 50 + l_Image.height());
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

