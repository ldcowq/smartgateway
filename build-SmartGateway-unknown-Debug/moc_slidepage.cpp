/****************************************************************************
** Meta object code from reading C++ file 'slidepage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SmartGateway/slidepage/slidepage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slidepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SlidePage_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SlidePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SlidePage_t qt_meta_stringdata_SlidePage = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SlidePage"
QT_MOC_LITERAL(1, 10, 22), // "hScrollBarValueChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 14), // "onStateChanged"
QT_MOC_LITERAL(4, 49, 16), // "QScroller::State"
QT_MOC_LITERAL(5, 66, 14) // "onTimerTimeOut"

    },
    "SlidePage\0hScrollBarValueChanged\0\0"
    "onStateChanged\0QScroller::State\0"
    "onTimerTimeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SlidePage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       3,    1,   32,    2, 0x08 /* Private */,
       5,    0,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,

       0        // eod
};

void SlidePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SlidePage *_t = static_cast<SlidePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->hScrollBarValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onStateChanged((*reinterpret_cast< QScroller::State(*)>(_a[1]))); break;
        case 2: _t->onTimerTimeOut(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SlidePage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SlidePage.data,
      qt_meta_data_SlidePage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SlidePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SlidePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SlidePage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SlidePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
