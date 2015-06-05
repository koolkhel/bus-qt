#ifndef GPSMODULE_H
#define GPSMODULE_H

#include "module.h"

class GPSModule: public Module
{
public:
    GPSModule();
    GPSModule(QString&);
    ~GPSModule();
    void start_simulation(double,double);
    void start();
    void stop();
};

#endif // GPSMODULE_H
