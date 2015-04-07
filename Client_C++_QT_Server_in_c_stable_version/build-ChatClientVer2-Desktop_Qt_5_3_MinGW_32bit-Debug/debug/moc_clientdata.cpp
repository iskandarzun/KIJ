/****************************************************************************
** Meta object code from reading C++ file 'clientdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ChatClient/clientdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClientData_t {
    QByteArrayData data[24];
    char stringdata[320];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientData_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientData_t qt_meta_stringdata_ClientData = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 11),
QT_MOC_LITERAL(4, 36, 18),
QT_MOC_LITERAL(5, 55, 13),
QT_MOC_LITERAL(6, 69, 13),
QT_MOC_LITERAL(7, 83, 13),
QT_MOC_LITERAL(8, 97, 14),
QT_MOC_LITERAL(9, 112, 11),
QT_MOC_LITERAL(10, 124, 11),
QT_MOC_LITERAL(11, 136, 18),
QT_MOC_LITERAL(12, 155, 13),
QT_MOC_LITERAL(13, 169, 13),
QT_MOC_LITERAL(14, 183, 13),
QT_MOC_LITERAL(15, 197, 14),
QT_MOC_LITERAL(16, 212, 9),
QT_MOC_LITERAL(17, 222, 10),
QT_MOC_LITERAL(18, 233, 10),
QT_MOC_LITERAL(19, 244, 10),
QT_MOC_LITERAL(20, 255, 16),
QT_MOC_LITERAL(21, 272, 16),
QT_MOC_LITERAL(22, 289, 18),
QT_MOC_LITERAL(23, 308, 11)
    },
    "ClientData\0getUsername\0\0getPassword\0"
    "getConfirmPassword\0getLoggedUser\0"
    "getChatFriend\0getSessionKey\0getOnlineUsers\0"
    "setUsername\0setPassword\0setConfirmPassword\0"
    "setLoggedUser\0setChatFriend\0setSessionKey\0"
    "setOnlineUsers\0clearData\0addNewUser\0"
    "removeUser\0usersCount\0validateUsername\0"
    "validatePassword\0confirmingPassword\0"
    "userAtIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x0a /* Public */,
       3,    0,  125,    2, 0x0a /* Public */,
       4,    0,  126,    2, 0x0a /* Public */,
       5,    0,  127,    2, 0x0a /* Public */,
       6,    0,  128,    2, 0x0a /* Public */,
       7,    0,  129,    2, 0x0a /* Public */,
       8,    0,  130,    2, 0x0a /* Public */,
       9,    1,  131,    2, 0x0a /* Public */,
      10,    1,  134,    2, 0x0a /* Public */,
      11,    1,  137,    2, 0x0a /* Public */,
      12,    0,  140,    2, 0x0a /* Public */,
      13,    1,  141,    2, 0x0a /* Public */,
      14,    1,  144,    2, 0x0a /* Public */,
      15,    1,  147,    2, 0x0a /* Public */,
      16,    0,  150,    2, 0x0a /* Public */,
      17,    1,  151,    2, 0x0a /* Public */,
      18,    1,  154,    2, 0x0a /* Public */,
      19,    0,  157,    2, 0x0a /* Public */,
      20,    0,  158,    2, 0x0a /* Public */,
      21,    0,  159,    2, 0x0a /* Public */,
      22,    0,  160,    2, 0x0a /* Public */,
      23,    1,  161,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QStringList,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::QString, QMetaType::Int,    2,

       0        // eod
};

void ClientData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientData *_t = static_cast<ClientData *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->getUsername();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->getPassword();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->getConfirmPassword();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->getLoggedUser();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { QString _r = _t->getChatFriend();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->getSessionKey();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { QStringList _r = _t->getOnlineUsers();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 7: _t->setUsername((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->setConfirmPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->setLoggedUser(); break;
        case 11: _t->setChatFriend((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setSessionKey((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->setOnlineUsers((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 14: _t->clearData(); break;
        case 15: _t->addNewUser((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->removeUser((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: { int _r = _t->usersCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { bool _r = _t->validateUsername();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { bool _r = _t->validatePassword();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 20: { bool _r = _t->confirmingPassword();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: { QString _r = _t->userAtIndex((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject ClientData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientData.data,
      qt_meta_data_ClientData,  qt_static_metacall, 0, 0}
};


const QMetaObject *ClientData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientData::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientData.stringdata))
        return static_cast<void*>(const_cast< ClientData*>(this));
    return QObject::qt_metacast(_clname);
}

int ClientData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
