/****************************************************************************
** Meta object code from reading C++ file 'connection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ChatClient/connection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Connection_t {
    QByteArrayData data[15];
    char stringdata[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Connection_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Connection_t qt_meta_stringdata_Connection = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 12),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 13),
QT_MOC_LITERAL(4, 39, 15),
QT_MOC_LITERAL(5, 55, 7),
QT_MOC_LITERAL(6, 63, 16),
QT_MOC_LITERAL(7, 80, 7),
QT_MOC_LITERAL(8, 88, 8),
QT_MOC_LITERAL(9, 97, 8),
QT_MOC_LITERAL(10, 106, 18),
QT_MOC_LITERAL(11, 125, 13),
QT_MOC_LITERAL(12, 139, 19),
QT_MOC_LITERAL(13, 159, 7),
QT_MOC_LITERAL(14, 167, 15)
    },
    "Connection\0incomingData\0\0connect_slots\0"
    "getServerAdress\0getPort\0setServerAddress\0"
    "setPort\0sendData\0readData\0ConnectingToServer\0"
    "disconnecting\0isConnectedToServer\0"
    "waiting\0emitSignalReady"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Connection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    1,   83,    2, 0x0a /* Public */,
       7,    1,   86,    2, 0x0a /* Public */,
       8,    6,   89,    2, 0x0a /* Public */,
       9,    0,  102,    2, 0x0a /* Public */,
      10,    0,  103,    2, 0x0a /* Public */,
      11,    0,  104,    2, 0x0a /* Public */,
      12,    0,  105,    2, 0x0a /* Public */,
      13,    0,  106,    2, 0x0a /* Public */,
      14,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,    2,    2,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Connection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Connection *_t = static_cast<Connection *>(_o);
        switch (_id) {
        case 0: _t->incomingData(); break;
        case 1: _t->connect_slots(); break;
        case 2: { QString _r = _t->getServerAdress();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->getPort();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: _t->setServerAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->setPort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sendData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 7: { QString _r = _t->readData();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: _t->ConnectingToServer(); break;
        case 9: _t->disconnecting(); break;
        case 10: { bool _r = _t->isConnectedToServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: _t->waiting(); break;
        case 12: _t->emitSignalReady(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Connection::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Connection::incomingData)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Connection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Connection.data,
      qt_meta_data_Connection,  qt_static_metacall, 0, 0}
};


const QMetaObject *Connection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Connection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Connection.stringdata))
        return static_cast<void*>(const_cast< Connection*>(this));
    return QObject::qt_metacast(_clname);
}

int Connection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Connection::incomingData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
