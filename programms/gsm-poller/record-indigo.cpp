// Copyright 2010, Indigo, Ltd.

#include <assert.h>
#include <errno.h>
#include <gps.h>                                  // gpsd
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <exception>
#include <string>

#include "./record-indigo.h"
#ifdef OLD_LOGGER
    #include "./log-indigo.h"
    static Logger *logger = LoggerFactory::getLogger("gps");
#else
    #include <QDebug>
#endif
#ifdef EVENTS_INDIGO
#include "./events-indigo.h"
#endif



Record::Record() {

	pthread_mutex_init(&access_lock, NULL);

	clear();
}

// копирование другой записи
Record::Record(const Record &other) {
	pthread_mutex_init(&access_lock, NULL);

	isValid = other.isValid;
	memcpy(&fix, &other.fix, sizeof(fix));
	unix_timestamp = other.unix_timestamp;
	satellites_visible = other.satellites_visible;
	satellites_used = other.satellites_used;
}

// копируем из other в себя
void Record::copy(const Record *other) {
	pthread_mutex_lock(&access_lock);

	isValid = other->isValid;
	memcpy(&fix, &other->fix, sizeof(fix));  // здесь fix -- структура, всё ок
	satellites_visible = other->satellites_visible;
	satellites_used = other->satellites_used;
	unix_timestamp = other->unix_timestamp;

	pthread_mutex_unlock(&access_lock);
}

// не стоит вызывать на боевом position, который заполняется потоком GPS
void Record::clear() {
	unix_timestamp = 0;
	satellites_visible = 0;
	satellites_used = 0;

	isValid = false;

	memset(&fix, 0, sizeof(fix));
}
