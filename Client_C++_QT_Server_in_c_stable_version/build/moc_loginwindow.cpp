/****************************************************************************
** Meta object code from reading C++ file 'loginwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ChatClient/loginwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoginWindow_t {
    QByteArrayData data[11];
    char stringdata[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_LoginWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_LoginWindow_t qt_meta_stringdata_LoginWindow = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 13),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 18),
QT_MOC_LITERAL(4, 46, 18),
QT_MOC_LITERAL(5, 65, 10),
QT_MOC_LITERAL(6, 76, 10),
QT_MOC_LITERAL(7, 87, 16),
QT_MOC_LITERAL(8, 104, 9),
QT_MOC_LITERAL(9, 114, 10),
QT_MOC_LITERAL(10, 125, 12)
    },
    "LoginWindow\0connect_slots\0\0"
    "usernameLoginInput\0passwordLoginInput\0"
    "loginStart\0backToMenu\0goToListUserMenu\0"
    "errorShow\0closeEvent\0QCloseEvent*\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a,
       3,    1,   55,    2, 0x08,
       4,    1,   58,    2, 0x08,
       5,    0,   61,    2, 0x08,
       6,    0,   62,    2, 0x08,
       7,    0,   63,    2, 0x08,
       8,    0,   64,    2, 0x08,
       9,    1,   65,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,

       0        // eod
};

void LoginWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoginWindow *_t = static_cast<LoginWindow *>(_o);
        switch (_id) {
        case 0: _t->connect_slots(); break;
        case 1: _t->usernameLoginInput((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->passwordLoginInput((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->loginStart(); break;
        case 4: _t->backToMenu(); break;
        case 5: _t->goToListUserMenu(); break;
        case 6: _t->errorShow(); break;
        case 7: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LoginWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LoginWindow.data,
      qt_meta_data_LoginWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWindow.stringdata))
        return static_cast<void*>(const_cast< LoginWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
