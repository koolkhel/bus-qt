// -*- mode: c++; -*-
// Copyright 2009,2010,2011 Bitterman

#ifndef _HOME_YURY_WORK_CLIENT_CPP_GPS_H_
#define _HOME_YURY_WORK_CLIENT_CPP_GPS_H_

#include <pthread.h>
#include <gps.h>

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


#endif  // _HOME_YURY_WORK_CLIENT_CPP_GPS_H_
