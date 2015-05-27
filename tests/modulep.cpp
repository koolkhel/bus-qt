#include "modulep.h"
#include <QString>

ModuleP::ModuleP(QString& host)
{
   nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
   publisher = new ZeroMQPublisher(host,context);
   subscriber = new ZeroMQSubscriber(context);
}

void ModuleP::printDebug()
{

}

