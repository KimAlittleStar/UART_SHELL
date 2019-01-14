/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../shell/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[18];
    char stringdata0[396];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 36), // "on_tEdit_shell_cursorPosition..."
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 23), // "on_pButton_send_clicked"
QT_MOC_LITERAL(4, 69, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(5, 93, 11), // "receiveInfo"
QT_MOC_LITERAL(6, 105, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(7, 127, 26), // "on_tEdit_shell_textChanged"
QT_MOC_LITERAL(8, 154, 12), // "on_timerOver"
QT_MOC_LITERAL(9, 167, 36), // "on_cBox_ColorList_currentText..."
QT_MOC_LITERAL(10, 204, 4), // "arg1"
QT_MOC_LITERAL(11, 209, 35), // "on_pButton_AddquickCompelat_c..."
QT_MOC_LITERAL(12, 245, 21), // "on_serialErrorOccured"
QT_MOC_LITERAL(13, 267, 19), // "on_Widget_destroyed"
QT_MOC_LITERAL(14, 287, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(15, 315, 5), // "index"
QT_MOC_LITERAL(16, 321, 35), // "on_pButton_delquickCompelat_c..."
QT_MOC_LITERAL(17, 357, 38) // "on_checkBox_caseSensitive_sta..."

    },
    "Widget\0on_tEdit_shell_cursorPositionChanged\0"
    "\0on_pButton_send_clicked\0"
    "on_pushButton_2_clicked\0receiveInfo\0"
    "on_pushButton_clicked\0on_tEdit_shell_textChanged\0"
    "on_timerOver\0on_cBox_ColorList_currentTextChanged\0"
    "arg1\0on_pButton_AddquickCompelat_clicked\0"
    "on_serialErrorOccured\0on_Widget_destroyed\0"
    "on_tabWidget_currentChanged\0index\0"
    "on_pButton_delquickCompelat_clicked\0"
    "on_checkBox_caseSensitive_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    1,   91,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    1,   97,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    1,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_tEdit_shell_cursorPositionChanged(); break;
        case 1: _t->on_pButton_send_clicked(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->receiveInfo(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_tEdit_shell_textChanged(); break;
        case 6: _t->on_timerOver(); break;
        case 7: _t->on_cBox_ColorList_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->on_pButton_AddquickCompelat_clicked(); break;
        case 9: _t->on_serialErrorOccured(); break;
        case 10: _t->on_Widget_destroyed(); break;
        case 11: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_pButton_delquickCompelat_clicked(); break;
        case 13: _t->on_checkBox_caseSensitive_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
