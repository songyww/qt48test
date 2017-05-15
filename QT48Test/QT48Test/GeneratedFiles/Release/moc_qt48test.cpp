/****************************************************************************
** Meta object code from reading C++ file 'qt48test.h'
**
** Created: Thu Dec 1 15:39:06 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qt48test.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt48test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QT48Test[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      20,    9,    9,    9, 0x08,
      30,    9,    9,    9, 0x08,
      41,    9,    9,    9, 0x08,
      51,    9,    9,    9, 0x08,
      64,    9,    9,    9, 0x08,
      74,    9,    9,    9, 0x08,
      83,    9,    9,    9, 0x08,
      98,    9,    9,    9, 0x08,
     105,    9,    9,    9, 0x08,
     121,    9,    9,    9, 0x08,
     137,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QT48Test[] = {
    "QT48Test\0\0fenkuai()\0opentif()\0opentif2()\0"
    "caijian()\0clearlayer()\0Onspeed()\0"
    "pinjie()\0linematching()\0surf()\0"
    "addtiftoglobe()\0adddemtoglobe()\0"
    "zoomtolayer()\0"
};

void QT48Test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QT48Test *_t = static_cast<QT48Test *>(_o);
        switch (_id) {
        case 0: _t->fenkuai(); break;
        case 1: _t->opentif(); break;
        case 2: _t->opentif2(); break;
        case 3: _t->caijian(); break;
        case 4: _t->clearlayer(); break;
        case 5: _t->Onspeed(); break;
        case 6: _t->pinjie(); break;
        case 7: _t->linematching(); break;
        case 8: _t->surf(); break;
        case 9: _t->addtiftoglobe(); break;
        case 10: _t->adddemtoglobe(); break;
        case 11: _t->zoomtolayer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QT48Test::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QT48Test::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QT48Test,
      qt_meta_data_QT48Test, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QT48Test::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QT48Test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QT48Test::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QT48Test))
        return static_cast<void*>(const_cast< QT48Test*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QT48Test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
