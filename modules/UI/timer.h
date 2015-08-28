#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>
#include <QTime>

class Timer :public QGraphicsTextItem
{
public:
    Timer(int startTime = QTime::currentTime().msecsSinceStartOfDay(), bool reverse = false);
    void setFormat(QString format);
    void changeTime(int time);
    void timerEvent ( QTimerEvent * event );
private:
    int currentTime;
    bool m_reverse;
    bool overflow;
    QString format;
};
#endif // TIMER_H
