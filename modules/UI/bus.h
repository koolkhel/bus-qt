#ifndef BUS_H
#define BUS_H
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QColor>

struct Bus {
public:
    Bus(QColor fontColor, QPixmap l_Image, QPoint pos = QPoint(0, 0));

    QGraphicsTextItem * name()  const;
    QGraphicsTextItem * time()  const;

    QGraphicsPixmapItem * image() const;
    void update(int time, const std::string &name) const;
    void show() const;
    void hide() const;
private:
    QGraphicsPixmapItem * m_image;
    QGraphicsTextItem *m_name, *m_time;
};

#endif // BUS_H
