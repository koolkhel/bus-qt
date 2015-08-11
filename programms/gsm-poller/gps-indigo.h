// -*- mode: c++; -*-
// Copyright 2009,2010,2011 Bitterman

#ifndef _HOME_YURY_WORK_CLIENT_CPP_GPS_H_
#define _HOME_YURY_WORK_CLIENT_CPP_GPS_H_

#include <pthread.h>
#include <stdbool.h>
#include <gps.h>

#include <string>

#define DUMMY_LATITUDE 39.0
#define DUMMY_LONGITUDE 42.0

void *poller(void *args);

/**
 * Текущая геопозиция
 */
class Record {
public:
	/// мютекс на доступ к позиции
	pthread_mutex_t access_lock;

	gps_fix_t fix;

	// let's save a unix timestamp here
	int unix_timestamp;

	// использовано столько спутников
	int satellites_used;

	// а вообще видно столько
	int satellites_visible;

	/// можно ли верить этой информации
	bool isValid;

	Record();
	Record(const Record &other);

	void copy(const Record *other);
	void clear();
};


/// Геопозиционирование
class GPS {
public:
    GPS();
    virtual ~GPS();
	/**
	 * Где мы в данный момент находимся?
	 *
	 * @param rec результат
	 */
	virtual void readRecord(Record *result);
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

#endif  // _HOME_YURY_WORK_CLIENT_CPP_GPS_H_
