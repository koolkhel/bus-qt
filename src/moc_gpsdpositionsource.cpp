/****************************************************************************
** Meta object code from reading C++ file 'gpsdpositionsource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gpsdpositionsource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpsdpositionsource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GpsdPositionSource_t {
    QByteArrayData data[12];
    char stringdata[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GpsdPositionSource_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GpsdPositionSource_t qt_meta_stringdata_GpsdPositionSource = {
    {
QT_MOC_LITERAL(0, 0, 18), // "GpsdPositionSource"
QT_MOC_LITERAL(1, 19, 15), // "positionUpdated"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "QGeoPositionInfo"
QT_MOC_LITERAL(4, 53, 6), // "update"
QT_MOC_LITERAL(5, 60, 13), // "updateTimeout"
QT_MOC_LITERAL(6, 74, 12), // "startUpdates"
QT_MOC_LITERAL(7, 87, 11), // "stopUpdates"
QT_MOC_LITERAL(8, 99, 13), // "requestUpdate"
QT_MOC_LITERAL(9, 113, 7), // "timeout"
QT_MOC_LITERAL(10, 121, 4), // "poll"
QT_MOC_LITERAL(11, 126, 11) // "connectGpsd"

    },
    "GpsdPositionSource\0positionUpdated\0\0"
    "QGeoPositionInfo\0update\0updateTimeout\0"
    "startUpdates\0stopUpdates\0requestUpdate\0"
    "timeout\0poll\0connectGpsd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GpsdPositionSource[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    1,   60,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x2a /* Public | MethodCloned */,
      10,    0,   64,    2, 0x08 /* Private */,
      11,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GpsdPositionSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GpsdPositionSource *_t = static_cast<GpsdPositionSource *>(_o);
        switch (_id) {
        case 0: _t->positionUpdated((*reinterpret_cast< const QGeoPositionInfo(*)>(_a[1]))); break;
        case 1: _t->updateTimeout(); break;
        case 2: _t->startUpdates(); break;
        case 3: _t->stopUpdates(); break;
        case 4: _t->requestUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->requestUpdate(); break;
        case 6: _t->poll(); break;
        case 7: _t->connectGpsd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GpsdPositionSource::*_t)(const QGeoPositionInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GpsdPositionSource::positionUpdated)) {
                *result = 0;
            }
        }
        {
            typedef void (GpsdPositionSource::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GpsdPositionSource::updateTimeout)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject GpsdPositionSource::staticMetaObject = {
    { &QGeoPositionInfoSource::staticMetaObject, qt_meta_stringdata_GpsdPositionSource.data,
      qt_meta_data_GpsdPositionSource,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GpsdPositionSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GpsdPositionSource::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GpsdPositionSource.stringdata))
        return static_cast<void*>(const_cast< GpsdPositionSource*>(this));
    return QGeoPositionInfoSource::qt_metacast(_clname);
}

int GpsdPositionSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGeoPositionInfoSource::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GpsdPositionSource::positionUpdated(const QGeoPositionInfo & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GpsdPositionSource::updateTimeout()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
