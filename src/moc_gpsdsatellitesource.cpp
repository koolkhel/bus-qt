/****************************************************************************
** Meta object code from reading C++ file 'gpsdsatellitesource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gpsdsatellitesource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpsdsatellitesource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GpsdSatelliteSource_t {
    QByteArrayData data[15];
    char stringdata[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GpsdSatelliteSource_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GpsdSatelliteSource_t qt_meta_stringdata_GpsdSatelliteSource = {
    {
QT_MOC_LITERAL(0, 0, 19), // "GpsdSatelliteSource"
QT_MOC_LITERAL(1, 20, 23), // "satellitesInViewUpdated"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 24), // "QList<QGeoSatelliteInfo>"
QT_MOC_LITERAL(4, 70, 10), // "satellites"
QT_MOC_LITERAL(5, 81, 22), // "satellitesInUseUpdated"
QT_MOC_LITERAL(6, 104, 14), // "requestTimeout"
QT_MOC_LITERAL(7, 119, 5), // "error"
QT_MOC_LITERAL(8, 125, 30), // "QGeoSatelliteInfoSource::Error"
QT_MOC_LITERAL(9, 156, 12), // "startUpdates"
QT_MOC_LITERAL(10, 169, 11), // "stopUpdates"
QT_MOC_LITERAL(11, 181, 13), // "requestUpdate"
QT_MOC_LITERAL(12, 195, 7), // "timeout"
QT_MOC_LITERAL(13, 203, 4), // "poll"
QT_MOC_LITERAL(14, 208, 11) // "connectGpsd"

    },
    "GpsdSatelliteSource\0satellitesInViewUpdated\0"
    "\0QList<QGeoSatelliteInfo>\0satellites\0"
    "satellitesInUseUpdated\0requestTimeout\0"
    "error\0QGeoSatelliteInfoSource::Error\0"
    "startUpdates\0stopUpdates\0requestUpdate\0"
    "timeout\0poll\0connectGpsd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GpsdSatelliteSource[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       6,    0,   70,    2, 0x06 /* Public */,
       7,    1,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   74,    2, 0x0a /* Public */,
      10,    0,   75,    2, 0x0a /* Public */,
      11,    1,   76,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x2a /* Public | MethodCloned */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GpsdSatelliteSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GpsdSatelliteSource *_t = static_cast<GpsdSatelliteSource *>(_o);
        switch (_id) {
        case 0: _t->satellitesInViewUpdated((*reinterpret_cast< const QList<QGeoSatelliteInfo>(*)>(_a[1]))); break;
        case 1: _t->satellitesInUseUpdated((*reinterpret_cast< const QList<QGeoSatelliteInfo>(*)>(_a[1]))); break;
        case 2: _t->requestTimeout(); break;
        case 3: _t->error((*reinterpret_cast< QGeoSatelliteInfoSource::Error(*)>(_a[1]))); break;
        case 4: _t->startUpdates(); break;
        case 5: _t->stopUpdates(); break;
        case 6: _t->requestUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->requestUpdate(); break;
        case 8: _t->poll(); break;
        case 9: _t->connectGpsd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GpsdSatelliteSource::*_t)(const QList<QGeoSatelliteInfo> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GpsdSatelliteSource::satellitesInViewUpdated)) {
                *result = 0;
            }
        }
        {
            typedef void (GpsdSatelliteSource::*_t)(const QList<QGeoSatelliteInfo> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GpsdSatelliteSource::satellitesInUseUpdated)) {
                *result = 1;
            }
        }
        {
            typedef void (GpsdSatelliteSource::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GpsdSatelliteSource::requestTimeout)) {
                *result = 2;
            }
        }
        {
            typedef void (GpsdSatelliteSource::*_t)(QGeoSatelliteInfoSource::Error );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GpsdSatelliteSource::error)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject GpsdSatelliteSource::staticMetaObject = {
    { &QGeoSatelliteInfoSource::staticMetaObject, qt_meta_stringdata_GpsdSatelliteSource.data,
      qt_meta_data_GpsdSatelliteSource,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GpsdSatelliteSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GpsdSatelliteSource::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GpsdSatelliteSource.stringdata))
        return static_cast<void*>(const_cast< GpsdSatelliteSource*>(this));
    return QGeoSatelliteInfoSource::qt_metacast(_clname);
}

int GpsdSatelliteSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGeoSatelliteInfoSource::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void GpsdSatelliteSource::satellitesInViewUpdated(const QList<QGeoSatelliteInfo> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GpsdSatelliteSource::satellitesInUseUpdated(const QList<QGeoSatelliteInfo> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GpsdSatelliteSource::requestTimeout()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void GpsdSatelliteSource::error(QGeoSatelliteInfoSource::Error _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
