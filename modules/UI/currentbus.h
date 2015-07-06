#ifndef CURRENTBUS_H
#define CURRENTBUS_H
#include "bus.h"
#include <QString>

class CurrentBus : public Bus
{
public:
    CurrentBus();
    CurrentBus(QString currentRouteTime, QString previousStationTime, QString nextStationTimeTable, QString nextStationForecasting);

    QString getPreviousStationTime() const;
    void setPreviousStationTime(const QString &value);

    QString getCurrentRouteTime() const;
    void setCurrentRouteTime(const QString &value);

    QString getNextStationTimeTable() const;
    void setNextStationTimeTable(const QString &value);

    QString getNextStationForecasting() const;
    void setNextStationForecasting(const QString &value);

private:
    QString previousStationTime;
    QString currentRouteTime;
    QString nextStationTimeTable;
    QString nextStationForecasting;
};

#endif // CURRENTBUS_H
