/****************************************************************************
** Meta object code from reading C++ file 'QtMainGame.h'
**
** Created: Mon 6. Jun 10:57:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QtMainGame.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtMainGame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtMainGame[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QtMainGame[] = {
    "QtMainGame\0\0timeout()\0timeOutSlot()\0"
};

const QMetaObject QtMainGame::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QtMainGame,
      qt_meta_data_QtMainGame, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtMainGame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtMainGame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtMainGame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMainGame))
        return static_cast<void*>(const_cast< QtMainGame*>(this));
    return QWidget::qt_metacast(_clname);
}

int QtMainGame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: timeout(); break;
        case 1: timeOutSlot(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QtMainGame::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
