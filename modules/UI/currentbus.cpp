#include "currentbus.h"

CurrentBus::CurrentBus()
{
    currentRouteTime = "";
    previousStationTime = "";
    nextStationTimeTable = "";
    nextStationForecasting = "";
}
QString CurrentBus::getPreviousStationTime() const
{
    return previousStationTime;
}

void CurrentBus::setPreviousStationTime(const QString &value)
{
    previousStationTime = value;
}
QString CurrentBus::getCurrentRouteTime() const
{
    return currentRouteTime;
}

void CurrentBus::setCurrentRouteTime(const QString &value)
{
    currentRouteTime = value;
}
QString CurrentBus::getNextStationTimeTable() const
{
    return nextStationTimeTable;
}

void CurrentBus::setNextStationTimeTable(const QString &value)
{
    nextStationTimeTable = value;
}
QString CurrentBus::getNextStationForecasting() const
{
    return nextStationForecasting;
}

void CurrentBus::setNextStationForecasting(const QString &value)
{
    nextStationForecasting = value;
}





