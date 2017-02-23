/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/glwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[25];
    char stringdata0[384];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 16), // "activaToonShader"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 17), // "activaPhongShader"
QT_MOC_LITERAL(4, 45, 19), // "activaGouraudShader"
QT_MOC_LITERAL(5, 65, 14), // "activaPhongTex"
QT_MOC_LITERAL(6, 80, 16), // "activaGouraudTex"
QT_MOC_LITERAL(7, 97, 17), // "activaBumpMapping"
QT_MOC_LITERAL(8, 115, 16), // "activaEnvMapping"
QT_MOC_LITERAL(9, 132, 16), // "ensenyaMenuLlum0"
QT_MOC_LITERAL(10, 149, 19), // "changePositionLight"
QT_MOC_LITERAL(11, 169, 22), // "changeDirectionalLight"
QT_MOC_LITERAL(12, 192, 15), // "changeSpotLight"
QT_MOC_LITERAL(13, 208, 13), // "activateLight"
QT_MOC_LITERAL(14, 222, 20), // "updateXPositionLight"
QT_MOC_LITERAL(15, 243, 9), // "xposition"
QT_MOC_LITERAL(16, 253, 20), // "updateYPositionLight"
QT_MOC_LITERAL(17, 274, 9), // "yposition"
QT_MOC_LITERAL(18, 284, 20), // "updateZPositionLight"
QT_MOC_LITERAL(19, 305, 9), // "zposition"
QT_MOC_LITERAL(20, 315, 20), // "updateLightIntensity"
QT_MOC_LITERAL(21, 336, 9), // "intensity"
QT_MOC_LITERAL(22, 346, 25), // "showAuxWindowPuntualLight"
QT_MOC_LITERAL(23, 372, 5), // "Llum*"
QT_MOC_LITERAL(24, 378, 5) // "light"

    },
    "GLWidget\0activaToonShader\0\0activaPhongShader\0"
    "activaGouraudShader\0activaPhongTex\0"
    "activaGouraudTex\0activaBumpMapping\0"
    "activaEnvMapping\0ensenyaMenuLlum0\0"
    "changePositionLight\0changeDirectionalLight\0"
    "changeSpotLight\0activateLight\0"
    "updateXPositionLight\0xposition\0"
    "updateYPositionLight\0yposition\0"
    "updateZPositionLight\0zposition\0"
    "updateLightIntensity\0intensity\0"
    "showAuxWindowPuntualLight\0Llum*\0light"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x0a /* Public */,
       3,    0,  100,    2, 0x0a /* Public */,
       4,    0,  101,    2, 0x0a /* Public */,
       5,    0,  102,    2, 0x0a /* Public */,
       6,    0,  103,    2, 0x0a /* Public */,
       7,    0,  104,    2, 0x0a /* Public */,
       8,    0,  105,    2, 0x0a /* Public */,
       9,    0,  106,    2, 0x0a /* Public */,
      10,    0,  107,    2, 0x0a /* Public */,
      11,    0,  108,    2, 0x0a /* Public */,
      12,    0,  109,    2, 0x0a /* Public */,
      13,    0,  110,    2, 0x0a /* Public */,
      14,    1,  111,    2, 0x0a /* Public */,
      16,    1,  114,    2, 0x0a /* Public */,
      18,    1,  117,    2, 0x0a /* Public */,
      20,    1,  120,    2, 0x0a /* Public */,
      22,    1,  123,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, 0x80000000 | 23,   24,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLWidget *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activaToonShader(); break;
        case 1: _t->activaPhongShader(); break;
        case 2: _t->activaGouraudShader(); break;
        case 3: _t->activaPhongTex(); break;
        case 4: _t->activaGouraudTex(); break;
        case 5: _t->activaBumpMapping(); break;
        case 6: _t->activaEnvMapping(); break;
        case 7: _t->ensenyaMenuLlum0(); break;
        case 8: _t->changePositionLight(); break;
        case 9: _t->changeDirectionalLight(); break;
        case 10: _t->changeSpotLight(); break;
        case 11: _t->activateLight(); break;
        case 12: _t->updateXPositionLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->updateYPositionLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->updateZPositionLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->updateLightIntensity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->showAuxWindowPuntualLight((*reinterpret_cast< Llum*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget.data,
      qt_meta_data_GLWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata0))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
