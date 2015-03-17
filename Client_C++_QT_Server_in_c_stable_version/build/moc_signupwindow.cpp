/****************************************************************************
** Meta object code from reading C++ file 'signupwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ChatClient/signupwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signupwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SignupWindow_t {
    QByteArrayData data[12];
    char stringdata[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SignupWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SignupWindow_t qt_meta_stringdata_SignupWindow = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 13),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 11),
QT_MOC_LITERAL(4, 40, 19),
QT_MOC_LITERAL(5, 60, 19),
QT_MOC_LITERAL(6, 80, 26),
QT_MOC_LITERAL(7, 107, 9),
QT_MOC_LITERAL(8, 117, 16),
QT_MOC_LITERAL(9, 134, 10),
QT_MOC_LITERAL(10, 145, 10),
QT_MOC_LITERAL(11, 156, 12)
    },
    "SignupWindow\0connect_slots\0\0signupStart\0"
    "signupUsernameInput\0signupPasswordInput\0"
    "signupConfirmPasswordInput\0errorShow\0"
    "goToListUserMenu\0backToMenu\0closeEvent\0"
    "QCloseEvent*\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SignupWindow[] = {

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
       4,    1,   61,    2, 0x08,
       5,    1,   64,    2, 0x08,
       6,    1,   67,    2, 0x08,
       7,    0,   70,    2, 0x08,
       8,    0,   71,    2, 0x08,
       9,    0,   72,    2, 0x08,
      10,    1,   73,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,

       0        // eod
};

void SignupWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SignupWindow *_t = static_cast<SignupWindow *>(_o);
        switch (_id) {
        case 0: _t->connect_slots(); break;
        case 1: _t->signupStart(); break;
        case 2: _t->signupUsernameInput((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->signupPasswordInput((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->signupConfirmPasswordInput((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->errorShow(); break;
        case 6: _t->goToListUserMenu(); break;
        case 7: _t->backToMenu(); break;
        case 8: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SignupWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SignupWindow.data,
      qt_meta_data_SignupWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *SignupWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SignupWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SignupWindow.stringdata))
        return static_cast<void*>(const_cast< SignupWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SignupWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
