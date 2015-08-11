#ifndef GPS_H
#define GPS_H

#include <stdbool.h>
#include <gps.h>

#include <string>
#include "record-indigo.h"
#define DUMMY_LATITUDE 39.0
#define DUMMY_LONGITUDE 42.0


/// Геопозиционирование
class GPS {
public:
    GPS() {}
    virtual ~GPS() {}
    /**
     * Где мы в данный момент находимся?
     *
     * @param rec результат
     */
    virtual void readRecord(Record *result) {}
protected:
    /// положение, которое периодически обновляется
    Record *record;
};

/// Использование gpsd для определения координат
class GPS_real : public GPS {
public:
    /// функция потока, которая обращается к gpsd и периодически обновляет
    /// текущую координату
    friend void *gps_poller(void *args);
    GPS_real();
    virtual ~GPS_real();
private:
    pthread_t poller_thread;
    volatile bool poller_finished;
};

/// Выдаёт фиксированную координату
class GPS_dummy : public GPS {
public:
    GPS_dummy();
};

#endif // GPS_H
