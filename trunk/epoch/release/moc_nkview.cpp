/****************************************************************************
** Meta object code from reading C++ file 'nkview.h'
**
** Created: Fri 11. Jun 04:17:38 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../nkview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nkview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NKView[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      20,    7,    7,    7, 0x05,
      34,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   54,    7,    7, 0x08,
     103,   54,    7,    7, 0x08,
     142,   54,    7,    7, 0x08,
     181,    7,    7,    7, 0x08,
     190,    7,    7,    7, 0x08,
     197,    7,    7,    7, 0x08,
     204,    7,    7,    7, 0x08,
     211,    7,    7,    7, 0x08,
     220,    7,    7,    7, 0x08,
     227,    7,    7,    7, 0x08,
     234,    7,    7,    7, 0x08,
     241,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NKView[] = {
    "NKView\0\0statusSig()\0itemClicked()\0"
    "itemDoubleClicked()\0item,column\0"
    "selectFromTree(QTreeWidgetItem*,int)\0"
    "selectFromppTree(QTreeWidgetItem*,int)\0"
    "selectFromtlTree(QTreeWidgetItem*,int)\0"
    "aepoha()\0adog()\0aPer()\0rPer()\0repoha()\0"
    "rdog()\0adel()\0acut()\0alink()\0"
};

const QMetaObject NKView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NKView,
      qt_meta_data_NKView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NKView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NKView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NKView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NKView))
        return static_cast<void*>(const_cast< NKView*>(this));
    return QWidget::qt_metacast(_clname);
}

int NKView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: statusSig(); break;
        case 1: itemClicked(); break;
        case 2: itemDoubleClicked(); break;
        case 3: selectFromTree((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: selectFromppTree((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: selectFromtlTree((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: aepoha(); break;
        case 7: adog(); break;
        case 8: aPer(); break;
        case 9: rPer(); break;
        case 10: repoha(); break;
        case 11: rdog(); break;
        case 12: adel(); break;
        case 13: acut(); break;
        case 14: alink(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void NKView::statusSig()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void NKView::itemClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void NKView::itemDoubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
