/****************************************************************************
** Meta object code from reading C++ file 'backend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "backend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Backend_t {
    QByteArrayData data[39];
    char stringdata[538];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Backend_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Backend_t qt_meta_stringdata_Backend = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Backend"
QT_MOC_LITERAL(1, 8, 16), // "protobuf_message"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 24), // "::indigo::pb::indigo_msg"
QT_MOC_LITERAL(4, 51, 7), // "message"
QT_MOC_LITERAL(5, 59, 17), // "connectedToServer"
QT_MOC_LITERAL(6, 77, 6), // "status"
QT_MOC_LITERAL(7, 84, 15), // "deviceIdChanged"
QT_MOC_LITERAL(8, 100, 8), // "deviceId"
QT_MOC_LITERAL(9, 109, 11), // "newPosition"
QT_MOC_LITERAL(10, 121, 14), // "QGeoCoordinate"
QT_MOC_LITERAL(11, 136, 10), // "coordinate"
QT_MOC_LITERAL(12, 147, 8), // "newSpeed"
QT_MOC_LITERAL(13, 156, 9), // "speed_kmh"
QT_MOC_LITERAL(14, 166, 17), // "newSatellitesUsed"
QT_MOC_LITERAL(15, 184, 14), // "satellitesUsed"
QT_MOC_LITERAL(16, 199, 13), // "movementStart"
QT_MOC_LITERAL(17, 213, 5), // "start"
QT_MOC_LITERAL(18, 219, 15), // "positionUpdated"
QT_MOC_LITERAL(19, 235, 16), // "QGeoPositionInfo"
QT_MOC_LITERAL(20, 252, 6), // "update"
QT_MOC_LITERAL(21, 259, 22), // "satellitesInUseUpdated"
QT_MOC_LITERAL(22, 282, 24), // "QList<QGeoSatelliteInfo>"
QT_MOC_LITERAL(23, 307, 13), // "satelliteInfo"
QT_MOC_LITERAL(24, 321, 17), // "sendMessageQueued"
QT_MOC_LITERAL(25, 339, 3), // "var"
QT_MOC_LITERAL(26, 343, 9), // "sendEvent"
QT_MOC_LITERAL(27, 353, 26), // "::indigo::pb::indigo_event"
QT_MOC_LITERAL(28, 380, 5), // "event"
QT_MOC_LITERAL(29, 386, 16), // "sendLocationData"
QT_MOC_LITERAL(30, 403, 9), // "readyRead"
QT_MOC_LITERAL(31, 413, 9), // "connected"
QT_MOC_LITERAL(32, 423, 5), // "error"
QT_MOC_LITERAL(33, 429, 29), // "QAbstractSocket::SocketError&"
QT_MOC_LITERAL(34, 459, 12), // "disconnected"
QT_MOC_LITERAL(35, 472, 9), // "reconnect"
QT_MOC_LITERAL(36, 482, 16), // "flushOrderEvents"
QT_MOC_LITERAL(37, 499, 12), // "send_message"
QT_MOC_LITERAL(38, 512, 25) // "::indigo::pb::indigo_msg&"

    },
    "Backend\0protobuf_message\0\0"
    "::indigo::pb::indigo_msg\0message\0"
    "connectedToServer\0status\0deviceIdChanged\0"
    "deviceId\0newPosition\0QGeoCoordinate\0"
    "coordinate\0newSpeed\0speed_kmh\0"
    "newSatellitesUsed\0satellitesUsed\0"
    "movementStart\0start\0positionUpdated\0"
    "QGeoPositionInfo\0update\0satellitesInUseUpdated\0"
    "QList<QGeoSatelliteInfo>\0satelliteInfo\0"
    "sendMessageQueued\0var\0sendEvent\0"
    "::indigo::pb::indigo_event\0event\0"
    "sendLocationData\0readyRead\0connected\0"
    "error\0QAbstractSocket::SocketError&\0"
    "disconnected\0reconnect\0flushOrderEvents\0"
    "send_message\0::indigo::pb::indigo_msg&"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Backend[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       5,    1,  112,    2, 0x06 /* Public */,
       7,    1,  115,    2, 0x06 /* Public */,
       9,    1,  118,    2, 0x06 /* Public */,
      12,    1,  121,    2, 0x06 /* Public */,
      14,    1,  124,    2, 0x06 /* Public */,
      16,    1,  127,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    1,  130,    2, 0x0a /* Public */,
      21,    1,  133,    2, 0x0a /* Public */,
      24,    1,  136,    2, 0x0a /* Public */,
      26,    1,  139,    2, 0x0a /* Public */,
      29,    0,  142,    2, 0x0a /* Public */,
      30,    0,  143,    2, 0x0a /* Public */,
      31,    0,  144,    2, 0x0a /* Public */,
      32,    1,  145,    2, 0x0a /* Public */,
      34,    0,  148,    2, 0x0a /* Public */,
      35,    0,  149,    2, 0x0a /* Public */,
      36,    0,  150,    2, 0x0a /* Public */,
      37,    1,  151,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   17,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 3,   25,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 33,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 38,   25,

       0        // eod
};

void Backend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Backend *_t = static_cast<Backend *>(_o);
        switch (_id) {
        case 0: _t->protobuf_message((*reinterpret_cast< ::indigo::pb::indigo_msg(*)>(_a[1]))); break;
        case 1: _t->connectedToServer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->deviceIdChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->newPosition((*reinterpret_cast< QGeoCoordinate(*)>(_a[1]))); break;
        case 4: _t->newSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->newSatellitesUsed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->movementStart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->positionUpdated((*reinterpret_cast< const QGeoPositionInfo(*)>(_a[1]))); break;
        case 8: _t->satellitesInUseUpdated((*reinterpret_cast< const QList<QGeoSatelliteInfo>(*)>(_a[1]))); break;
        case 9: _t->sendMessageQueued((*reinterpret_cast< ::indigo::pb::indigo_msg(*)>(_a[1]))); break;
        case 10: _t->sendEvent((*reinterpret_cast< ::indigo::pb::indigo_event(*)>(_a[1]))); break;
        case 11: _t->sendLocationData(); break;
        case 12: _t->readyRead(); break;
        case 13: _t->connected(); break;
        case 14: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 15: _t->disconnected(); break;
        case 16: _t->reconnect(); break;
        case 17: _t->flushOrderEvents(); break;
        case 18: _t->send_message((*reinterpret_cast< ::indigo::pb::indigo_msg(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGeoCoordinate >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Backend::*_t)(::indigo::pb::indigo_msg );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::protobuf_message)) {
                *result = 0;
            }
        }
        {
            typedef void (Backend::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::connectedToServer)) {
                *result = 1;
            }
        }
        {
            typedef void (Backend::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::deviceIdChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (Backend::*_t)(QGeoCoordinate );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::newPosition)) {
                *result = 3;
            }
        }
        {
            typedef void (Backend::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::newSpeed)) {
                *result = 4;
            }
        }
        {
            typedef void (Backend::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::newSatellitesUsed)) {
                *result = 5;
            }
        }
        {
            typedef void (Backend::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Backend::movementStart)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject Backend::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Backend.data,
      qt_meta_data_Backend,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Backend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Backend::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Backend.stringdata))
        return static_cast<void*>(const_cast< Backend*>(this));
    return QObject::qt_metacast(_clname);
}

int Backend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Backend::protobuf_message(::indigo::pb::indigo_msg _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Backend::connectedToServer(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Backend::deviceIdChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Backend::newPosition(QGeoCoordinate _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Backend::newSpeed(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Backend::newSatellitesUsed(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Backend::movementStart(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
