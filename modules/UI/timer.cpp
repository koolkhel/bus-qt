#include "timer.h"
Timer::Timer(int startTime, bool reverse) {
    setDefaultTextColor(Qt::white);
    currentTime = startTime;
    m_reverse = reverse;
    overflow = false;
    startTimer(1000);
    format = "hh:mm:ss";
}

void Timer::setFormat(QString l_format)
{
    format = l_format;
}

void Timer::changeTime(int time)
{
    currentTime = time;
    if(overflow) {
        overflow = false;
        m_reverse = !m_reverse;
    }
}

void Timer::timerEvent(QTimerEvent *event)
{
    (void)event;
    currentTime += 1000 -m_reverse*2000;
    if(currentTime < 0) {
        currentTime -= currentTime*2;
        overflow = true;
        m_reverse = !m_reverse;
    }
    setPlainText(QString("%1%2")
                 .arg((overflow) ? "-" : "")
                 .arg(QTime::fromMSecsSinceStartOfDay(currentTime).toString(format)));

}
