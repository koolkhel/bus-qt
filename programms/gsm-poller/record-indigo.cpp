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

#include "./gps-indigo.h"
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


// нехорошо, что поллер так и торчит своим именем
void *gps_poller(void *args) {
	GPS_real *obj = reinterpret_cast<GPS_real *>(args);

	bool have_carrier = false;
	int result = 0;
	// время последнего изменения состояния gps
	time_t last_state_change_time = 0;

	struct gps_data_t gps_data;

	bool gpsd_connected = false;
	do {
	    result = gps_open("127.0.0.1", DEFAULT_GPSD_PORT, &gps_data);
	    /* если упало -- делать дальше нечего */
	    if (result != 0) {
	        fprintf(stderr, "cannot connect to local gpsd, retrying\n");
	        sleep(10);
	    } else
	        gpsd_connected = true;
	} while (!gpsd_connected);
	assert(result == 0);
#ifdef OLD_LOGGER
	logger_debug("gps connected ok");
#else
    qDebug() << "gps connected ok";
#endif
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

	while (!obj->poller_finished) {
		// ждём 3 секунды сообщений от gpsd
		if (!gps_waiting(&gps_data, 3000))
			continue;

		if (gps_read(&gps_data) == -1) {
			// ошибка -- посмотреть, бывает ли у нас вообще такая ситуация
#ifdef OLD_LOGGER
			logger_debug_once("can't read gps data\n");
#else
            qDebug() << "can`t read gps data";
#endif
			continue;
		}

		pthread_mutex_lock(&obj->record->access_lock);

		if ((gps_data.status == STATUS_FIX) &&
		    (gps_data.fix.mode == MODE_2D ||
		     gps_data.fix.mode == MODE_3D)) {

			if (!have_carrier &&
			    (time(NULL) - last_state_change_time > 60)) {
				have_carrier = true;
#ifdef EVENTS_INDIGO
				EventsReport::reportGPSOn();
#endif
#ifdef OLD_LOGGER
				logger_debug("got carrier");
#else
                qDebug() << "got carrier";
#endif
				last_state_change_time = time(NULL);
			}

			// we could get 0 sometimes.
			if ((fabs(gps_data.fix.latitude) > 0.1) &&
			    (fabs(gps_data.fix.longitude) > 0.1)) {
				obj->record->isValid = true;
			} else {
#ifdef OLD_LOGGER
				logger_debug_once("zero record");
#else
                qDebug() << "zero record";
#endif
			}

			obj->record->fix = gps_data.fix;
			obj->record->satellites_used = gps_data.satellites_used;
			obj->record->satellites_visible = gps_data.satellites_visible;

		} else if ((gps_data.status == STATUS_NO_FIX) ||
			   (gps_data.fix.mode == MODE_NO_FIX) ||
			   (gps_data.fix.mode == MODE_NOT_SEEN)) {

			/* запись получена, но GPSом в ней не пахло */
			if (have_carrier &&
			    (time(NULL) - last_state_change_time > 60)) {
				have_carrier = false;
#ifdef EVENTS_INDIGO
				EventsReport::reportGPSOff();
#endif

#ifdef OLD_LOGGER
				logger_debug("lost carrier");
#else
                qDebug() << "lost carrier";
#endif
				last_state_change_time = time(NULL);
			}

			obj->record->satellites_used = 0;
			obj->record->satellites_visible = 0;

			obj->record->isValid = false;
        } else {
#ifdef OLD_LOGGER
			logger_debug_once("got fix with wrong mode");
#else
            qDebug() << "got fix with wrong mode";
#endif
        }

		obj->record->unix_timestamp = time(NULL);

		pthread_mutex_unlock(&obj->record->access_lock);
	}

	gps_stream(&gps_data, WATCH_DISABLE, NULL);
	gps_close(&gps_data);
#ifdef OLD_LOGGER
	logger_debug("gps finished ok");
#else
    qDebug() << "gps finished ok";
#endif

	return NULL;
}

GPS_real::GPS_real() {
    poller_finished = false;
    pthread_create(&poller_thread, NULL, &gps_poller, this);
}

GPS_real::~GPS_real() {
    poller_finished = true;
    pthread_join(poller_thread, NULL);
}

GPS_dummy::GPS_dummy() {
    record->fix.mode = MODE_2D;
    record->fix.latitude = DUMMY_LATITUDE;
    record->fix.longitude = DUMMY_LONGITUDE;
    record->satellites_visible = 10;
    record->satellites_used = 5;
    record->isValid = true;
    record->fix.speed = 0;
#ifdef OLD_LOGGER
    logger_debug("dummy gps set up");
#else
    qDebug() << "dummy gps set up";
#endif
}
