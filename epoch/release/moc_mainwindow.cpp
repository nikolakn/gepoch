/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri 11. Jun 04:22:55 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      23,   11,   11,   11, 0x08,
      30,   11,   11,   11, 0x08,
      38,   11,   11,   11, 0x08,
      45,   11,   11,   11, 0x08,
      52,   11,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      68,   11,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
      95,   11,   11,   11, 0x08,
     105,   11,   11,   11, 0x08,
     111,   11,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,
     139,  124,   11,   11, 0x08,
     174,   11,   11,   11, 0x08,
     187,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     226,  221,   11,   11, 0x08,
     253,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0newEpoch()\0save()\0print()\0"
    "open()\0undo()\0about()\0mleft()\0mright()\0"
    "status()\0zoomin()\0zoomout()\0cut()\0"
    "del()\0link()\0property,value\0"
    "valueChanged(QtProperty*,QVariant)\0"
    "decChanged()\0itemClicked()\0"
    "itemDoubleClicked()\0size\0"
    "kategorijaChanged(QString)\0godinaChanged()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newEpoch(); break;
        case 1: save(); break;
        case 2: print(); break;
        case 3: open(); break;
        case 4: undo(); break;
        case 5: about(); break;
        case 6: mleft(); break;
        case 7: mright(); break;
        case 8: status(); break;
        case 9: zoomin(); break;
        case 10: zoomout(); break;
        case 11: cut(); break;
        case 12: del(); break;
        case 13: link(); break;
        case 14: valueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 15: decChanged(); break;
        case 16: itemClicked(); break;
        case 17: itemDoubleClicked(); break;
        case 18: kategorijaChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: godinaChanged(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
