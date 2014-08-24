/****************************************************************************
** Meta object code from reading C++ file 'abilitypanel.h'
**
** Created: Tue 14. Jun 13:52:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "abilitypanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abilitypanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_abilityPanel[] = {

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
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      24,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_abilityPanel[] = {
    "abilityPanel\0\0clicked()\0buttonClicked()\0"
};

const QMetaObject abilityPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_abilityPanel,
      qt_meta_data_abilityPanel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &abilityPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *abilityPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *abilityPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_abilityPanel))
        return static_cast<void*>(const_cast< abilityPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int abilityPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked(); break;
        case 1: buttonClicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void abilityPanel::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
