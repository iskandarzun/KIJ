/****************************************************************************
** Meta object code from reading C++ file 'menuwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ChatClient/menuwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MenuWindow_t {
    QByteArrayData data[17];
    char stringdata[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MenuWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MenuWindow_t qt_meta_stringdata_MenuWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 13),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 10),
QT_MOC_LITERAL(4, 37, 9),
QT_MOC_LITERAL(5, 47, 11),
QT_MOC_LITERAL(6, 59, 10),
QT_MOC_LITERAL(7, 70, 10),
QT_MOC_LITERAL(8, 81, 17),
QT_MOC_LITERAL(9, 99, 18),
QT_MOC_LITERAL(10, 118, 17),
QT_MOC_LITERAL(11, 136, 8),
QT_MOC_LITERAL(12, 145, 11),
QT_MOC_LITERAL(13, 157, 11),
QT_MOC_LITERAL(14, 169, 6),
QT_MOC_LITERAL(15, 176, 11),
QT_MOC_LITERAL(16, 188, 12)
    },
    "MenuWindow\0connect_slots\0\0goToSignup\0"
    "goToLogin\0checkSignup\0checkLogin\0"
    "backToMenu\0setListUserOnline\0"
    "setListUserOffline\0getBufferProtocol\0"
    "addUsers\0sendMessage\0standByRead\0"
    "logout\0initMessage\0clearMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    1,   95,    2, 0x08 /* Private */,
       9,    1,   98,    2, 0x08 /* Private */,
      10,    1,  101,    2, 0x08 /* Private */,
      11,    1,  104,    2, 0x08 /* Private */,
      12,    0,  107,    2, 0x08 /* Private */,
      13,    0,  108,    2, 0x08 /* Private */,
      14,    0,  109,    2, 0x08 /* Private */,
      15,    0,  110,    2, 0x08 /* Private */,
      16,    0,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::QStringList, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MenuWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MenuWindow *_t = static_cast<MenuWindow *>(_o);
        switch (_id) {
        case 0: _t->connect_slots(); break;
        case 1: _t->goToSignup(); break;
        case 2: _t->goToLogin(); break;
        case 3: _t->checkSignup(); break;
        case 4: _t->checkLogin(); break;
        case 5: _t->backToMenu(); break;
        case 6: _t->setListUserOnline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setListUserOffline((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: { QStringList _r = _t->getBufferProtocol((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 9: _t->addUsers((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->sendMessage(); break;
        case 11: _t->standByRead(); break;
        case 12: _t->logout(); break;
        case 13: _t->initMessage(); break;
        case 14: _t->clearMessage(); break;
        default: ;
        }
    }
}

const QMetaObject MenuWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MenuWindow.data,
      qt_meta_data_MenuWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MenuWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuWindow.stringdata))
        return static_cast<void*>(const_cast< MenuWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MenuWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
