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
    QByteArrayData data[28];
    char stringdata0[383];
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
QT_MOC_LITERAL(7, 74, 15), // "updateDht11Data"
QT_MOC_LITERAL(8, 90, 12), // "updateMqData"
QT_MOC_LITERAL(9, 103, 20), // "sendKitchenHeartBeat"
QT_MOC_LITERAL(10, 124, 8), // "deviceId"
QT_MOC_LITERAL(11, 133, 5), // "state"
QT_MOC_LITERAL(12, 139, 23), // "sendLivingRoomHeartBeat"
QT_MOC_LITERAL(13, 163, 14), // "noSensorSignal"
QT_MOC_LITERAL(14, 178, 8), // "finished"
QT_MOC_LITERAL(15, 187, 11), // "onlineCheck"
QT_MOC_LITERAL(16, 199, 9), // "shortAddr"
QT_MOC_LITERAL(17, 209, 27), // "pSerialPort_onErrorOccurred"
QT_MOC_LITERAL(18, 237, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(19, 266, 7), // "working"
QT_MOC_LITERAL(20, 274, 15), // "onMqttConnected"
QT_MOC_LITERAL(21, 290, 14), // "onMqttReceived"
QT_MOC_LITERAL(22, 305, 7), // "message"
QT_MOC_LITERAL(23, 313, 17), // "onLivingRoomLight"
QT_MOC_LITERAL(24, 331, 6), // "status"
QT_MOC_LITERAL(25, 338, 16), // "onLivingRoomBeep"
QT_MOC_LITERAL(26, 355, 14), // "onkitchenLight"
QT_MOC_LITERAL(27, 370, 12) // "onkitchenFan"

    },
    "GetSensorDataBySerial\0updateSensorData\0"
    "\0temperature\0humidity\0carbon\0smoke\0"
    "updateDht11Data\0updateMqData\0"
    "sendKitchenHeartBeat\0deviceId\0state\0"
    "sendLivingRoomHeartBeat\0noSensorSignal\0"
    "finished\0onlineCheck\0shortAddr\0"
    "pSerialPort_onErrorOccurred\0"
    "QSerialPort::SerialPortError\0working\0"
    "onMqttConnected\0onMqttReceived\0message\0"
    "onLivingRoomLight\0status\0onLivingRoomBeep\0"
    "onkitchenLight\0onkitchenFan"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GetSensorDataBySerial[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  134,    2, 0x06 /* Public */,
       1,    3,  143,    2, 0x26 /* Public | MethodCloned */,
       1,    2,  150,    2, 0x26 /* Public | MethodCloned */,
       1,    1,  155,    2, 0x26 /* Public | MethodCloned */,
       1,    0,  158,    2, 0x26 /* Public | MethodCloned */,
       7,    2,  159,    2, 0x06 /* Public */,
       7,    1,  164,    2, 0x26 /* Public | MethodCloned */,
       7,    0,  167,    2, 0x26 /* Public | MethodCloned */,
       8,    2,  168,    2, 0x06 /* Public */,
       8,    1,  173,    2, 0x26 /* Public | MethodCloned */,
       8,    0,  176,    2, 0x26 /* Public | MethodCloned */,
       9,    2,  177,    2, 0x06 /* Public */,
      12,    2,  182,    2, 0x06 /* Public */,
      13,    0,  187,    2, 0x06 /* Public */,
      14,    0,  188,    2, 0x06 /* Public */,
      15,    1,  189,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  192,    2, 0x0a /* Public */,
      19,    0,  195,    2, 0x0a /* Public */,
      20,    0,  196,    2, 0x0a /* Public */,
      21,    1,  197,    2, 0x0a /* Public */,
      23,    1,  200,    2, 0x0a /* Public */,
      25,    1,  203,    2, 0x0a /* Public */,
      26,    1,  206,    2, 0x0a /* Public */,
      27,    1,  209,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   22,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString,   24,

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
        case 5: _t->updateDht11Data((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->updateDht11Data((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->updateDht11Data(); break;
        case 8: _t->updateMqData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->updateMqData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->updateMqData(); break;
        case 11: _t->sendKitchenHeartBeat((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->sendLivingRoomHeartBeat((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->noSensorSignal(); break;
        case 14: _t->finished(); break;
        case 15: _t->onlineCheck((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->pSerialPort_onErrorOccurred((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 17: _t->working(); break;
        case 18: _t->onMqttConnected(); break;
        case 19: _t->onMqttReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 20: _t->onLivingRoomLight((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->onLivingRoomBeep((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->onkitchenLight((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->onkitchenFan((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
            using _t = void (GetSensorDataBySerial::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::updateDht11Data)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GetSensorDataBySerial::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::updateMqData)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GetSensorDataBySerial::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::sendKitchenHeartBeat)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (GetSensorDataBySerial::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::sendLivingRoomHeartBeat)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (GetSensorDataBySerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::noSensorSignal)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (GetSensorDataBySerial::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::finished)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (GetSensorDataBySerial::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetSensorDataBySerial::onlineCheck)) {
                *result = 15;
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
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
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
void GetSensorDataBySerial::updateDht11Data(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 8
void GetSensorDataBySerial::updateMqData(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 11
void GetSensorDataBySerial::sendKitchenHeartBeat(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void GetSensorDataBySerial::sendLivingRoomHeartBeat(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void GetSensorDataBySerial::noSensorSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void GetSensorDataBySerial::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void GetSensorDataBySerial::onlineCheck(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
