#include "bus.h"

Bus::Bus()
{
    time = "";
    label = "";
    image = "";
}
QString Bus::getTime() const
{
    return time;
}

void Bus::setTime(const QString &value)
{
    time = value;
}
QString Bus::getLabel() const
{
    return label;
}

void Bus::setLabel(const QString &value)
{
    label = value;
}
QString Bus::getImage() const
{
    return image;
}

void Bus::setImage(const QString &value)
{
    image = value;
}



