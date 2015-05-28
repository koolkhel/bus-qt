#include "modulep.h"
#include <QString>

ModuleP::ModuleP(QString& string)
{

}


ZeroMQPublisher *ModuleP::getPublisher() const
{
    return publisher;
}

void ModuleP::setPublisher(ZeroMQPublisher *value)
{
    publisher = value;
}

ZeroMQSubscriber *ModuleP::getSubscriber() const
{
    return subscriber;
}

void ModuleP::setSubscriber(ZeroMQSubscriber *value)
{
    subscriber = value;
}
void ModuleP::printDebug()
{

}

