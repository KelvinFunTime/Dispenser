/****************************************************************************
** Meta object code from reading C++ file 'Timer.h'
**
** Created: Tue Apr 9 04:09:52 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qt-gui/Timer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Timer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Timer_Label[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Timer_Label[] = {
    "Timer_Label\0update_label()\0\0"
};

void Timer_Label::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Timer_Label *_t = static_cast<Timer_Label *>(_o);
        switch (_id) {
        case 0: _t->update_label(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Timer_Label::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Timer_Label::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Timer_Label,
      qt_meta_data_Timer_Label, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Timer_Label::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Timer_Label::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Timer_Label::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Timer_Label))
        return static_cast<void*>(const_cast< Timer_Label*>(this));
    return QObject::qt_metacast(_clname);
}

int Timer_Label::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_Timer_Level[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Timer_Level[] = {
    "Timer_Level\0update_level()\0\0"
};

void Timer_Level::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Timer_Level *_t = static_cast<Timer_Level *>(_o);
        switch (_id) {
        case 0: _t->update_level(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Timer_Level::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Timer_Level::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Timer_Level,
      qt_meta_data_Timer_Level, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Timer_Level::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Timer_Level::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Timer_Level::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Timer_Level))
        return static_cast<void*>(const_cast< Timer_Level*>(this));
    return QObject::qt_metacast(_clname);
}

int Timer_Level::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
