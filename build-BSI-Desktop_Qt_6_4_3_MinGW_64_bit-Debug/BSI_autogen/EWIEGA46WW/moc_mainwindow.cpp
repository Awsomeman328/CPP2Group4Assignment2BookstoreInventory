/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../BSI/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
<<<<<<< Updated upstream
    uint offsetsAndSizes[44];
=======
    uint offsetsAndSizes[46];
>>>>>>> Stashed changes
    char stringdata0[11];
    char stringdata1[9];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[10];
    char stringdata5[9];
    char stringdata6[6];
    char stringdata7[12];
    char stringdata8[12];
    char stringdata9[10];
    char stringdata10[10];
    char stringdata11[20];
    char stringdata12[10];
    char stringdata13[25];
    char stringdata14[21];
    char stringdata15[20];
    char stringdata16[21];
    char stringdata17[16];
    char stringdata18[11];
    char stringdata19[20];
    char stringdata20[23];
    char stringdata21[11];
<<<<<<< Updated upstream
=======
    char stringdata22[32];
>>>>>>> Stashed changes
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 8),  // "createDB"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 11),  // "createTable"
        QT_MOC_LITERAL(33, 9),  // "readTable"
        QT_MOC_LITERAL(43, 8),  // "searchDB"
        QT_MOC_LITERAL(52, 5),  // "logIn"
        QT_MOC_LITERAL(58, 11),  // "exitProgram"
        QT_MOC_LITERAL(70, 11),  // "addBookToDB"
        QT_MOC_LITERAL(82, 9),  // "importCSV"
        QT_MOC_LITERAL(92, 9),  // "exportCSV"
        QT_MOC_LITERAL(102, 19),  // "toggleAdminFeatures"
        QT_MOC_LITERAL(122, 9),  // "isEnabled"
        QT_MOC_LITERAL(132, 24),  // "searchBookToShoppingList"
        QT_MOC_LITERAL(157, 20),  // "searchBookToBookList"
        QT_MOC_LITERAL(178, 19),  // "displayShoppingList"
        QT_MOC_LITERAL(198, 20),  // "purchaseShoppingList"
        QT_MOC_LITERAL(219, 15),  // "displayBookList"
        QT_MOC_LITERAL(235, 10),  // "addNewUser"
        QT_MOC_LITERAL(246, 19),  // "changeUsersPassword"
        QT_MOC_LITERAL(266, 22),  // "checkValidBookToUpdate"
<<<<<<< Updated upstream
        QT_MOC_LITERAL(289, 10)   // "updateBook"
=======
        QT_MOC_LITERAL(289, 10),  // "updateBook"
        QT_MOC_LITERAL(300, 31)   // "on_pushButtonAddNewUser_clicked"
>>>>>>> Stashed changes
    },
    "MainWindow",
    "createDB",
    "",
    "createTable",
    "readTable",
    "searchDB",
    "logIn",
    "exitProgram",
    "addBookToDB",
    "importCSV",
    "exportCSV",
    "toggleAdminFeatures",
    "isEnabled",
    "searchBookToShoppingList",
    "searchBookToBookList",
    "displayShoppingList",
    "purchaseShoppingList",
    "displayBookList",
    "addNewUser",
    "changeUsersPassword",
    "checkValidBookToUpdate",
<<<<<<< Updated upstream
    "updateBook"
=======
    "updateBook",
    "on_pushButtonAddNewUser_clicked"
>>>>>>> Stashed changes
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
<<<<<<< Updated upstream
      19,   14, // methods
=======
      20,   14, // methods
>>>>>>> Stashed changes
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
<<<<<<< Updated upstream
       1,    0,  128,    2, 0x0a,    1 /* Public */,
       3,    0,  129,    2, 0x0a,    2 /* Public */,
       4,    0,  130,    2, 0x0a,    3 /* Public */,
       5,    0,  131,    2, 0x0a,    4 /* Public */,
       6,    0,  132,    2, 0x0a,    5 /* Public */,
       7,    0,  133,    2, 0x0a,    6 /* Public */,
       8,    0,  134,    2, 0x0a,    7 /* Public */,
       9,    0,  135,    2, 0x0a,    8 /* Public */,
      10,    0,  136,    2, 0x0a,    9 /* Public */,
      11,    1,  137,    2, 0x0a,   10 /* Public */,
      13,    0,  140,    2, 0x0a,   12 /* Public */,
      14,    0,  141,    2, 0x0a,   13 /* Public */,
      15,    0,  142,    2, 0x0a,   14 /* Public */,
      16,    0,  143,    2, 0x0a,   15 /* Public */,
      17,    0,  144,    2, 0x0a,   16 /* Public */,
      18,    0,  145,    2, 0x0a,   17 /* Public */,
      19,    0,  146,    2, 0x0a,   18 /* Public */,
      20,    0,  147,    2, 0x0a,   19 /* Public */,
      21,    0,  148,    2, 0x0a,   20 /* Public */,
=======
       1,    0,  134,    2, 0x0a,    1 /* Public */,
       3,    0,  135,    2, 0x0a,    2 /* Public */,
       4,    0,  136,    2, 0x0a,    3 /* Public */,
       5,    0,  137,    2, 0x0a,    4 /* Public */,
       6,    0,  138,    2, 0x0a,    5 /* Public */,
       7,    0,  139,    2, 0x0a,    6 /* Public */,
       8,    0,  140,    2, 0x0a,    7 /* Public */,
       9,    0,  141,    2, 0x0a,    8 /* Public */,
      10,    0,  142,    2, 0x0a,    9 /* Public */,
      11,    1,  143,    2, 0x0a,   10 /* Public */,
      13,    0,  146,    2, 0x0a,   12 /* Public */,
      14,    0,  147,    2, 0x0a,   13 /* Public */,
      15,    0,  148,    2, 0x0a,   14 /* Public */,
      16,    0,  149,    2, 0x0a,   15 /* Public */,
      17,    0,  150,    2, 0x0a,   16 /* Public */,
      18,    0,  151,    2, 0x0a,   17 /* Public */,
      19,    0,  152,    2, 0x0a,   18 /* Public */,
      20,    0,  153,    2, 0x0a,   19 /* Public */,
      21,    0,  154,    2, 0x0a,   20 /* Public */,
      22,    0,  155,    2, 0x08,   21 /* Private */,
>>>>>>> Stashed changes

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
<<<<<<< Updated upstream
=======
    QMetaType::Void,
>>>>>>> Stashed changes

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'createDB'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchDB'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'logIn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitProgram'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addBookToDB'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'importCSV'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exportCSV'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleAdminFeatures'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'searchBookToShoppingList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchBookToBookList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayShoppingList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'purchaseShoppingList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'displayBookList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNewUser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'changeUsersPassword'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkValidBookToUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateBook'
<<<<<<< Updated upstream
=======
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonAddNewUser_clicked'
>>>>>>> Stashed changes
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->createDB(); break;
        case 1: _t->createTable(); break;
        case 2: _t->readTable(); break;
        case 3: _t->searchDB(); break;
        case 4: _t->logIn(); break;
        case 5: _t->exitProgram(); break;
        case 6: _t->addBookToDB(); break;
        case 7: _t->importCSV(); break;
        case 8: _t->exportCSV(); break;
        case 9: _t->toggleAdminFeatures((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->searchBookToShoppingList(); break;
        case 11: _t->searchBookToBookList(); break;
        case 12: _t->displayShoppingList(); break;
        case 13: _t->purchaseShoppingList(); break;
        case 14: _t->displayBookList(); break;
        case 15: _t->addNewUser(); break;
        case 16: _t->changeUsersPassword(); break;
        case 17: _t->checkValidBookToUpdate(); break;
        case 18: _t->updateBook(); break;
<<<<<<< Updated upstream
=======
        case 19: _t->on_pushButtonAddNewUser_clicked(); break;
>>>>>>> Stashed changes
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
<<<<<<< Updated upstream
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
=======
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 20;
>>>>>>> Stashed changes
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
