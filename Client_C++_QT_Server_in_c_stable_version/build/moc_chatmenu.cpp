/****************************************************************************
** Meta object code from reading C++ file 'chatmenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ChatClient/chatmenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChatMenu_t {
    QByteArrayData data[8];
    char stringdata[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ChatMenu_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ChatMenu_t qt_meta_stringdata_ChatMenu = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 13),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 6),
QT_MOC_LITERAL(4, 31, 13),
QT_MOC_LITERAL(5, 45, 19),
QT_MOC_LITERAL(6, 65, 9),
QT_MOC_LITERAL(7, 75, 11)
    },
    "ChatMenu\0setChatFriend\0\0string\0"
    "getChatFriend\0setActiveChatFriend\0"
    "showEvent\0QShowEvent*\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a,
       4,    0,   37,    2, 0x0a,
       5,    0,   38,    2, 0x0a,
       6,    1,   39,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    0x80000000 | 3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void ChatMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChatMenu *_t = static_cast<ChatMenu *>(_o);
        switch (_id) {
        case 0: _t->setChatFriend((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 1: { string _r = _t->getChatFriend();
            if (_a[0]) *reinterpret_cast< string*>(_a[0]) = _r; }  break;
        case 2: _t->setActiveChatFriend(); break;
        case 3: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ChatMenu::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ChatMenu.data,
      qt_meta_data_ChatMenu,  qt_static_metacall, 0, 0}
};


const QMetaObject *ChatMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChatMenu.stringdata))
        return static_cast<void*>(const_cast< ChatMenu*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ChatMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
