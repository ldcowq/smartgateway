/****************************************************************************
** Meta object code from reading C++ file 'getsensordatabyserial.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SmartGateway/environment/getsensordatabyserial.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getsensordatabyserial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GetSensorDataBySerial_t {
    QByteArrayData data[15];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GetSensorDataBySerial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GetSensorDataBySerial_t qt_meta_stringdata_GetSensorDataBySerial = {
    {
QT_MOC_LITERAL(0, 0, 21), // "GetSensorDataBySerial"
QT_MOC_LITERAL(1, 22, 16), // "updateSensorData"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 11), // "temperature"
QT_MOC_LITERAL(4, 52, 8), // "humidity"
QT_MOC_LITERAL(5, 61, 6), // "carbon"
QT_MOC_LITERAL(6, 68, 5), // "smoke"
QT_MOC_LITERAL(7, 74, 14), // "noSensorSignal"
QT_MOC_LITERAL(8, 89, 8), // "finished"
QT_MOC_LITERAL(9, 98, 27), // "pSerialPort_onErrorOccurred"
QT_MOC_LITERAL(10, 126, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(11, 155, 7), // "working"
QT_MOC_LITERAL(12, 163, 15), // "onMqttConnected"
QT_MOC_LITERAL(13, 179, 14), // "onMqttReceived"
QT_MOC_LITERAL(14, 194, 7) // "message"

    },
    "GetSensorDataBySerial\0updateSensorData\0"
    "\0temperature\0humidity\0carbon\0smoke\0"
    "noSensorSignal\0finished\0"
    "pSerialPort_onErrorOccurred\0"
    "QSerialPort::SerialPortError\0working\0"
    "onMqttConnected\0onMqttReceived\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GetSensorDataBySerial[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   69,    2, 0x06 /* Public */,
       1,    3,   78,    2, 0x26 /* Public | MethodCloned */,
       1,    2,   85,    2, 0x26 /* Public | MethodCloned */,
       1,    1,   90,    2, 0x26 /* Public | MethodCloned */,
       1,    0,   93,    2, 0x26 /* Public | MethodCloned */,
       7,    0,   94,    2, 0x06 /* Public */,
       8,    0,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   96,    2, 0x0a /* Public */,
      11,    0,   99,    2, 0x0a /* Public */,
      12,    0,  100,    2, 0x0a /* Public */,
      13,    1,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   14,

       0        // eod
};

void GetSensorDataBySerial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GetSensorDataBySerial *_t = static_cast<GetSensorDataBySerial *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSensorData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->updateSensorData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->updateSensorData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->updateSensorData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateSensorData(); break;
        case 5: _t->noSensorSignal(); break;
        case 6: _t->finished(); break;
        case 7: _t->pSerialPort_onErrorOccurred((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 8: _t->working(); break;
        case 9: _t->onMqttConnected(); break;
        case 10: _t->onMqttReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GetSensorDataBySerial::*)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::updateSensorData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GetSensorDataBySerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::noSensorSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GetSensorDataBySerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::finished)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GetSensorDataBySerial::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GetSensorDataBySerial.data,
      qt_meta_data_GetSensorDataBySerial,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GetSensorDataBySerial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GetSensorDataBySerial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GetSensorDataBySerial.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GetSensorDataBySerial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void GetSensorDataBySerial::updateSensorData(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 5
void GetSensorDataBySerial::noSensorSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void GetSensorDataBySerial::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
