#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>
#include <QTime>

class Timer :public QGraphicsTextItem
{
public:
    enum TimerType {
        COMMON = 0,
        ABSOLUTE_TIME = 1
    };

    Timer(TimerType type = COMMON, int startTime = QTime::currentTime().msecsSinceStartOfDay(), bool reverse = false);
    void setFormat(QString format);
    void changeTime(int time);
    void timerEvent ( QTimerEvent * event );
private:
    int currentTime;
    bool m_reverse;
    bool overflow;
    QString format;
    TimerType m_type;
};
#endif // TIMER_H
