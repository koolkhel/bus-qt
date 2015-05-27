/****************************************************************************
** Meta object code from reading C++ file 'nzmqt.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nzmqt/include/nzmqt/nzmqt.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nzmqt.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_nzmqt__ZMQSocket_t {
    QByteArrayData data[52];
    char stringdata[563];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_nzmqt__ZMQSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_nzmqt__ZMQSocket_t qt_meta_stringdata_nzmqt__ZMQSocket = {
    {
QT_MOC_LITERAL(0, 0, 16), // "nzmqt::ZMQSocket"
QT_MOC_LITERAL(1, 17, 15), // "messageReceived"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "close"
QT_MOC_LITERAL(4, 40, 11), // "sendMessage"
QT_MOC_LITERAL(5, 52, 6), // "bytes_"
QT_MOC_LITERAL(6, 59, 27), // "nzmqt::ZMQSocket::SendFlags"
QT_MOC_LITERAL(7, 87, 6), // "flags_"
QT_MOC_LITERAL(8, 94, 4), // "msg_"
QT_MOC_LITERAL(9, 99, 4), // "Type"
QT_MOC_LITERAL(10, 104, 7), // "TYP_PUB"
QT_MOC_LITERAL(11, 112, 7), // "TYP_SUB"
QT_MOC_LITERAL(12, 120, 8), // "TYP_PUSH"
QT_MOC_LITERAL(13, 129, 8), // "TYP_PULL"
QT_MOC_LITERAL(14, 138, 7), // "TYP_REQ"
QT_MOC_LITERAL(15, 146, 7), // "TYP_REP"
QT_MOC_LITERAL(16, 154, 10), // "TYP_DEALER"
QT_MOC_LITERAL(17, 165, 10), // "TYP_ROUTER"
QT_MOC_LITERAL(18, 176, 8), // "TYP_PAIR"
QT_MOC_LITERAL(19, 185, 8), // "TYP_XPUB"
QT_MOC_LITERAL(20, 194, 8), // "TYP_XSUB"
QT_MOC_LITERAL(21, 203, 5), // "Event"
QT_MOC_LITERAL(22, 209, 10), // "EVT_POLLIN"
QT_MOC_LITERAL(23, 220, 11), // "EVT_POLLOUT"
QT_MOC_LITERAL(24, 232, 11), // "EVT_POLLERR"
QT_MOC_LITERAL(25, 244, 6), // "Events"
QT_MOC_LITERAL(26, 251, 8), // "SendFlag"
QT_MOC_LITERAL(27, 260, 8), // "SND_MORE"
QT_MOC_LITERAL(28, 269, 11), // "SND_NOBLOCK"
QT_MOC_LITERAL(29, 281, 9), // "SendFlags"
QT_MOC_LITERAL(30, 291, 11), // "ReceiveFlag"
QT_MOC_LITERAL(31, 303, 11), // "RCV_NOBLOCK"
QT_MOC_LITERAL(32, 315, 12), // "ReceiveFlags"
QT_MOC_LITERAL(33, 328, 6), // "Option"
QT_MOC_LITERAL(34, 335, 8), // "OPT_TYPE"
QT_MOC_LITERAL(35, 344, 11), // "OPT_RCVMORE"
QT_MOC_LITERAL(36, 356, 6), // "OPT_FD"
QT_MOC_LITERAL(37, 363, 10), // "OPT_EVENTS"
QT_MOC_LITERAL(38, 374, 13), // "OPT_SUBSCRIBE"
QT_MOC_LITERAL(39, 388, 15), // "OPT_UNSUBSCRIBE"
QT_MOC_LITERAL(40, 404, 12), // "OPT_AFFINITY"
QT_MOC_LITERAL(41, 417, 12), // "OPT_IDENTITY"
QT_MOC_LITERAL(42, 430, 8), // "OPT_RATE"
QT_MOC_LITERAL(43, 439, 16), // "OPT_RECOVERY_IVL"
QT_MOC_LITERAL(44, 456, 10), // "OPT_SNDBUF"
QT_MOC_LITERAL(45, 467, 10), // "OPT_RCVBUF"
QT_MOC_LITERAL(46, 478, 10), // "OPT_LINGER"
QT_MOC_LITERAL(47, 489, 17), // "OPT_RECONNECT_IVL"
QT_MOC_LITERAL(48, 507, 21), // "OPT_RECONNECT_IVL_MAX"
QT_MOC_LITERAL(49, 529, 11), // "OPT_BACKLOG"
QT_MOC_LITERAL(50, 541, 10), // "OPT_SNDHWM"
QT_MOC_LITERAL(51, 552, 10) // "OPT_RCVHWM"

    },
    "nzmqt::ZMQSocket\0messageReceived\0\0"
    "close\0sendMessage\0bytes_\0"
    "nzmqt::ZMQSocket::SendFlags\0flags_\0"
    "msg_\0Type\0TYP_PUB\0TYP_SUB\0TYP_PUSH\0"
    "TYP_PULL\0TYP_REQ\0TYP_REP\0TYP_DEALER\0"
    "TYP_ROUTER\0TYP_PAIR\0TYP_XPUB\0TYP_XSUB\0"
    "Event\0EVT_POLLIN\0EVT_POLLOUT\0EVT_POLLERR\0"
    "Events\0SendFlag\0SND_MORE\0SND_NOBLOCK\0"
    "SendFlags\0ReceiveFlag\0RCV_NOBLOCK\0"
    "ReceiveFlags\0Option\0OPT_TYPE\0OPT_RCVMORE\0"
    "OPT_FD\0OPT_EVENTS\0OPT_SUBSCRIBE\0"
    "OPT_UNSUBSCRIBE\0OPT_AFFINITY\0OPT_IDENTITY\0"
    "OPT_RATE\0OPT_RECOVERY_IVL\0OPT_SNDBUF\0"
    "OPT_RCVBUF\0OPT_LINGER\0OPT_RECONNECT_IVL\0"
    "OPT_RECONNECT_IVL_MAX\0OPT_BACKLOG\0"
    "OPT_SNDHWM\0OPT_RCVHWM"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nzmqt__ZMQSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       8,   64, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   47,    2, 0x0a /* Public */,
       4,    2,   48,    2, 0x0a /* Public */,
       4,    1,   53,    2, 0x2a /* Public | MethodCloned */,
       4,    2,   56,    2, 0x0a /* Public */,
       4,    1,   61,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArrayList,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QByteArray, 0x80000000 | 6,    5,    7,
    QMetaType::Bool, QMetaType::QByteArray,    5,
    QMetaType::Bool, QMetaType::QByteArrayList, 0x80000000 | 6,    8,    7,
    QMetaType::Bool, QMetaType::QByteArrayList,    8,

 // enums: name, flags, count, data
       9, 0x0,   11,   96,
      21, 0x1,    3,  118,
      25, 0x1,    3,  124,
      26, 0x1,    2,  130,
      29, 0x1,    2,  134,
      30, 0x1,    1,  138,
      32, 0x1,    1,  140,
      33, 0x0,   18,  142,

 // enum data: key, value
      10, uint(nzmqt::ZMQSocket::TYP_PUB),
      11, uint(nzmqt::ZMQSocket::TYP_SUB),
      12, uint(nzmqt::ZMQSocket::TYP_PUSH),
      13, uint(nzmqt::ZMQSocket::TYP_PULL),
      14, uint(nzmqt::ZMQSocket::TYP_REQ),
      15, uint(nzmqt::ZMQSocket::TYP_REP),
      16, uint(nzmqt::ZMQSocket::TYP_DEALER),
      17, uint(nzmqt::ZMQSocket::TYP_ROUTER),
      18, uint(nzmqt::ZMQSocket::TYP_PAIR),
      19, uint(nzmqt::ZMQSocket::TYP_XPUB),
      20, uint(nzmqt::ZMQSocket::TYP_XSUB),
      22, uint(nzmqt::ZMQSocket::EVT_POLLIN),
      23, uint(nzmqt::ZMQSocket::EVT_POLLOUT),
      24, uint(nzmqt::ZMQSocket::EVT_POLLERR),
      22, uint(nzmqt::ZMQSocket::EVT_POLLIN),
      23, uint(nzmqt::ZMQSocket::EVT_POLLOUT),
      24, uint(nzmqt::ZMQSocket::EVT_POLLERR),
      27, uint(nzmqt::ZMQSocket::SND_MORE),
      28, uint(nzmqt::ZMQSocket::SND_NOBLOCK),
      27, uint(nzmqt::ZMQSocket::SND_MORE),
      28, uint(nzmqt::ZMQSocket::SND_NOBLOCK),
      31, uint(nzmqt::ZMQSocket::RCV_NOBLOCK),
      31, uint(nzmqt::ZMQSocket::RCV_NOBLOCK),
      34, uint(nzmqt::ZMQSocket::OPT_TYPE),
      35, uint(nzmqt::ZMQSocket::OPT_RCVMORE),
      36, uint(nzmqt::ZMQSocket::OPT_FD),
      37, uint(nzmqt::ZMQSocket::OPT_EVENTS),
      38, uint(nzmqt::ZMQSocket::OPT_SUBSCRIBE),
      39, uint(nzmqt::ZMQSocket::OPT_UNSUBSCRIBE),
      40, uint(nzmqt::ZMQSocket::OPT_AFFINITY),
      41, uint(nzmqt::ZMQSocket::OPT_IDENTITY),
      42, uint(nzmqt::ZMQSocket::OPT_RATE),
      43, uint(nzmqt::ZMQSocket::OPT_RECOVERY_IVL),
      44, uint(nzmqt::ZMQSocket::OPT_SNDBUF),
      45, uint(nzmqt::ZMQSocket::OPT_RCVBUF),
      46, uint(nzmqt::ZMQSocket::OPT_LINGER),
      47, uint(nzmqt::ZMQSocket::OPT_RECONNECT_IVL),
      48, uint(nzmqt::ZMQSocket::OPT_RECONNECT_IVL_MAX),
      49, uint(nzmqt::ZMQSocket::OPT_BACKLOG),
      50, uint(nzmqt::ZMQSocket::OPT_SNDHWM),
      51, uint(nzmqt::ZMQSocket::OPT_RCVHWM),

       0        // eod
};

void nzmqt::ZMQSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZMQSocket *_t = static_cast<ZMQSocket *>(_o);
        switch (_id) {
        case 0: _t->messageReceived((*reinterpret_cast< const QList<QByteArray>(*)>(_a[1]))); break;
        case 1: _t->close(); break;
        case 2: { bool _r = _t->sendMessage((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< nzmqt::ZMQSocket::SendFlags(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->sendMessage((*reinterpret_cast< const QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->sendMessage((*reinterpret_cast< const QList<QByteArray>(*)>(_a[1])),(*reinterpret_cast< nzmqt::ZMQSocket::SendFlags(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->sendMessage((*reinterpret_cast< const QList<QByteArray>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< nzmqt::ZMQSocket::SendFlags >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< nzmqt::ZMQSocket::SendFlags >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZMQSocket::*_t)(const QList<QByteArray> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZMQSocket::messageReceived)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject nzmqt::ZMQSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_nzmqt__ZMQSocket.data,
      qt_meta_data_nzmqt__ZMQSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *nzmqt::ZMQSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nzmqt::ZMQSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_nzmqt__ZMQSocket.stringdata))
        return static_cast<void*>(const_cast< ZMQSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int nzmqt::ZMQSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void nzmqt::ZMQSocket::messageReceived(const QList<QByteArray> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_nzmqt__ZMQContext_t {
    QByteArrayData data[3];
    char stringdata[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_nzmqt__ZMQContext_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_nzmqt__ZMQContext_t qt_meta_stringdata_nzmqt__ZMQContext = {
    {
QT_MOC_LITERAL(0, 0, 17), // "nzmqt::ZMQContext"
QT_MOC_LITERAL(1, 18, 14), // "contextStopped"
QT_MOC_LITERAL(2, 33, 0) // ""

    },
    "nzmqt::ZMQContext\0contextStopped\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nzmqt__ZMQContext[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void nzmqt::ZMQContext::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZMQContext *_t = static_cast<ZMQContext *>(_o);
        switch (_id) {
        case 0: _t->contextStopped(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZMQContext::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZMQContext::contextStopped)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject nzmqt::ZMQContext::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_nzmqt__ZMQContext.data,
      qt_meta_data_nzmqt__ZMQContext,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *nzmqt::ZMQContext::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nzmqt::ZMQContext::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_nzmqt__ZMQContext.stringdata))
        return static_cast<void*>(const_cast< ZMQContext*>(this));
    return QObject::qt_metacast(_clname);
}

int nzmqt::ZMQContext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void nzmqt::ZMQContext::contextStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_nzmqt__PollingZMQSocket_t {
    QByteArrayData data[1];
    char stringdata[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_nzmqt__PollingZMQSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_nzmqt__PollingZMQSocket_t qt_meta_stringdata_nzmqt__PollingZMQSocket = {
    {
QT_MOC_LITERAL(0, 0, 23) // "nzmqt::PollingZMQSocket"

    },
    "nzmqt::PollingZMQSocket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nzmqt__PollingZMQSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void nzmqt::PollingZMQSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject nzmqt::PollingZMQSocket::staticMetaObject = {
    { &ZMQSocket::staticMetaObject, qt_meta_stringdata_nzmqt__PollingZMQSocket.data,
      qt_meta_data_nzmqt__PollingZMQSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *nzmqt::PollingZMQSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nzmqt::PollingZMQSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_nzmqt__PollingZMQSocket.stringdata))
        return static_cast<void*>(const_cast< PollingZMQSocket*>(this));
    return ZMQSocket::qt_metacast(_clname);
}

int nzmqt::PollingZMQSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZMQSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_nzmqt__PollingZMQContext_t {
    QByteArrayData data[8];
    char stringdata[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_nzmqt__PollingZMQContext_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_nzmqt__PollingZMQContext_t qt_meta_stringdata_nzmqt__PollingZMQContext = {
    {
QT_MOC_LITERAL(0, 0, 24), // "nzmqt::PollingZMQContext"
QT_MOC_LITERAL(1, 25, 9), // "pollError"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "errorNum"
QT_MOC_LITERAL(4, 45, 8), // "errorMsg"
QT_MOC_LITERAL(5, 54, 3), // "run"
QT_MOC_LITERAL(6, 58, 4), // "poll"
QT_MOC_LITERAL(7, 63, 8) // "timeout_"

    },
    "nzmqt::PollingZMQContext\0pollError\0\0"
    "errorNum\0errorMsg\0run\0poll\0timeout_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nzmqt__PollingZMQContext[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   39,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Long,    7,
    QMetaType::Void,

       0        // eod
};

void nzmqt::PollingZMQContext::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PollingZMQContext *_t = static_cast<PollingZMQContext *>(_o);
        switch (_id) {
        case 0: _t->pollError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->run(); break;
        case 2: _t->poll((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 3: _t->poll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PollingZMQContext::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PollingZMQContext::pollError)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject nzmqt::PollingZMQContext::staticMetaObject = {
    { &ZMQContext::staticMetaObject, qt_meta_stringdata_nzmqt__PollingZMQContext.data,
      qt_meta_data_nzmqt__PollingZMQContext,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *nzmqt::PollingZMQContext::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nzmqt::PollingZMQContext::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_nzmqt__PollingZMQContext.stringdata))
        return static_cast<void*>(const_cast< PollingZMQContext*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< PollingZMQContext*>(this));
    return ZMQContext::qt_metacast(_clname);
}

int nzmqt::PollingZMQContext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZMQContext::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void nzmqt::PollingZMQContext::pollError(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_nzmqt__SocketNotifierZMQSocket_t {
    QByteArrayData data[3];
    char stringdata[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_nzmqt__SocketNotifierZMQSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_nzmqt__SocketNotifierZMQSocket_t qt_meta_stringdata_nzmqt__SocketNotifierZMQSocket = {
    {
QT_MOC_LITERAL(0, 0, 30), // "nzmqt::SocketNotifierZMQSocket"
QT_MOC_LITERAL(1, 31, 18), // "socketReadActivity"
QT_MOC_LITERAL(2, 50, 0) // ""

    },
    "nzmqt::SocketNotifierZMQSocket\0"
    "socketReadActivity\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nzmqt__SocketNotifierZMQSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void nzmqt::SocketNotifierZMQSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SocketNotifierZMQSocket *_t = static_cast<SocketNotifierZMQSocket *>(_o);
        switch (_id) {
        case 0: _t->socketReadActivity(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject nzmqt::SocketNotifierZMQSocket::staticMetaObject = {
    { &ZMQSocket::staticMetaObject, qt_meta_stringdata_nzmqt__SocketNotifierZMQSocket.data,
      qt_meta_data_nzmqt__SocketNotifierZMQSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *nzmqt::SocketNotifierZMQSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nzmqt::SocketNotifierZMQSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_nzmqt__SocketNotifierZMQSocket.stringdata))
        return static_cast<void*>(const_cast< SocketNotifierZMQSocket*>(this));
    return ZMQSocket::qt_metacast(_clname);
}

int nzmqt::SocketNotifierZMQSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZMQSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_nzmqt__SocketNotifierZMQContext_t {
    QByteArrayData data[1];
    char stringdata[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_nzmqt__SocketNotifierZMQContext_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_nzmqt__SocketNotifierZMQContext_t qt_meta_stringdata_nzmqt__SocketNotifierZMQContext = {
    {
QT_MOC_LITERAL(0, 0, 31) // "nzmqt::SocketNotifierZMQContext"

    },
    "nzmqt::SocketNotifierZMQContext"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nzmqt__SocketNotifierZMQContext[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void nzmqt::SocketNotifierZMQContext::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject nzmqt::SocketNotifierZMQContext::staticMetaObject = {
    { &ZMQContext::staticMetaObject, qt_meta_stringdata_nzmqt__SocketNotifierZMQContext.data,
      qt_meta_data_nzmqt__SocketNotifierZMQContext,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *nzmqt::SocketNotifierZMQContext::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nzmqt::SocketNotifierZMQContext::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_nzmqt__SocketNotifierZMQContext.stringdata))
        return static_cast<void*>(const_cast< SocketNotifierZMQContext*>(this));
    return ZMQContext::qt_metacast(_clname);
}

int nzmqt::SocketNotifierZMQContext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ZMQContext::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
