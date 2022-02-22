/****************************************************************************
** Meta object code from reading C++ file 'environment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SmartGateway/environment/environment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'environment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Environment_t {
    QByteArrayData data[7];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Environment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Environment_t qt_meta_stringdata_Environment = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Environment"
QT_MOC_LITERAL(1, 12, 15), // "livingRoomLight"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 6), // "status"
QT_MOC_LITERAL(4, 36, 14), // "livingRoomBeep"
QT_MOC_LITERAL(5, 51, 12), // "kitchenLight"
QT_MOC_LITERAL(6, 64, 10) // "kitchenFan"

    },
    "Environment\0livingRoomLight\0\0status\0"
    "livingRoomBeep\0kitchenLight\0kitchenFan"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Environment[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       5,    1,   40,    2, 0x06 /* Public */,
       6,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void Environment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Environment *_t = static_cast<Environment *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->livingRoomLight((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->livingRoomBeep((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->kitchenLight((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->kitchenFan((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Environment::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Environment::livingRoomLight)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Environment::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Environment::livingRoomBeep)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Environment::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Environment::kitchenLight)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Environment::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Environment::kitchenFan)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Environment::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Environment.data,
      qt_meta_data_Environment,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Environment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Environment::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Environment.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Environment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void Environment::livingRoomLight(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Environment::livingRoomBeep(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Environment::kitchenLight(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Environment::kitchenFan(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
