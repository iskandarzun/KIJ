/****************************************************************************
** Meta object code from reading C++ file 'listuserwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ChatClient/listuserwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listuserwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ListUserWindow_t {
    QByteArrayData data[11];
    char stringdata[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ListUserWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ListUserWindow_t qt_meta_stringdata_ListUserWindow = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 13),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 17),
QT_MOC_LITERAL(4, 48, 18),
QT_MOC_LITERAL(5, 67, 9),
QT_MOC_LITERAL(6, 77, 12),
QT_MOC_LITERAL(7, 90, 6),
QT_MOC_LITERAL(8, 97, 9),
QT_MOC_LITERAL(9, 107, 14),
QT_MOC_LITERAL(10, 122, 13)
    },
    "ListUserWindow\0connect_slots\0\0"
    "setActiveUsername\0setDataOnlineUsers\0"
    "chatStart\0openChatMenu\0logout\0errorShow\0"
    "activateWindow\0setChatFriend\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListUserWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a,
       3,    0,   60,    2, 0x08,
       4,    0,   61,    2, 0x08,
       5,    0,   62,    2, 0x08,
       6,    0,   63,    2, 0x08,
       7,    0,   64,    2, 0x08,
       8,    0,   65,    2, 0x08,
       9,    0,   66,    2, 0x08,
      10,    1,   67,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void ListUserWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListUserWindow *_t = static_cast<ListUserWindow *>(_o);
        switch (_id) {
        case 0: _t->connect_slots(); break;
        case 1: _t->setActiveUsername(); break;
        case 2: _t->setDataOnlineUsers(); break;
        case 3: _t->chatStart(); break;
        case 4: _t->openChatMenu(); break;
        case 5: _t->logout(); break;
        case 6: _t->errorShow(); break;
        case 7: _t->activateWindow(); break;
        case 8: _t->setChatFriend((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ListUserWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ListUserWindow.data,
      qt_meta_data_ListUserWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *ListUserWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListUserWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ListUserWindow.stringdata))
        return static_cast<void*>(const_cast< ListUserWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ListUserWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
