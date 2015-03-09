/****************************************************************************
** Meta object code from reading C++ file 'Talk2WatchInterface.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/T2W API/Talk2WatchInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Talk2WatchInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Talk2WatchInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      49,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      26,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      41,   20,   20,   20, 0x05,
      63,   20,   20,   20, 0x05,
      84,   77,   20,   20, 0x05,
     111,  103,   20,   20, 0x05,
     157,  142,   20,   20, 0x05,
     194,  103,   20,   20, 0x05,
     224,  142,   20,   20, 0x05,
     260,  103,   20,   20, 0x05,
     291,  142,   20,   20, 0x05,
     337,  328,   20,   20, 0x05,
     362,   20,   20,   20, 0x05,
     397,  389,   20,   20, 0x05,
     443,  428,   20,   20, 0x05,
     480,  389,   20,   20, 0x05,
     510,  428,   20,   20, 0x05,
     546,  389,   20,   20, 0x05,
     577,  428,   20,   20, 0x05,
     620,  614,   20,   20, 0x05,
     653,  614,   20,   20, 0x05,
     701,  687,   20,   20, 0x05,
     753,  614,   20,   20, 0x05,
     773,  614,   20,   20, 0x05,
     796,  792,   20,   20, 0x05,
     831,  821,   20,   20, 0x05,
     864,  821,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     904,  898,   20,   20, 0x0a,
     926,   20,   20,   20, 0x0a,

 // methods: signature, parameters, type, tag, flags
     952,   20,  947,   20, 0x02,
     976,   20,  947,   20, 0x02,
    1003,   20,  947,   20, 0x02,
    1051, 1037,   20,   20, 0x02,
    1099, 1076,   20,   20, 0x02,
    1192, 1134,   20,   20, 0x02,
    1254,   20,   20,   20, 0x02,
    1313, 1284,   20,   20, 0x02,
    1388, 1351,   20,   20, 0x02,
    1441, 1434,   20,   20, 0x02,
    1484, 1463,   20,   20, 0x02,
    1514,   20,   20,   20, 0x02,
    1533,  103,   20,   20, 0x02,
    1555,  389,   20,   20, 0x02,
    1597, 1577,   20,   20, 0x02,
    1627, 1577,   20,   20, 0x02,
    1657,   20,   20,   20, 0x02,
    1677,  687,   20,   20, 0x02,
    1725,  614,   20,   20, 0x02,
    1755,  614,   20,   20, 0x02,
    1791,  614,   20,   20, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Talk2WatchInterface[] = {
    "Talk2WatchInterface\0\0transmissionReady()\0"
    "receivedData(QString)\0authSuccess()\0"
    "_error\0authError(QString)\0_action\0"
    "actionCreationSuccess(QString)\0"
    "_action,_error\0actionCreationError(QString,QString)\0"
    "actionRemovalSuccess(QString)\0"
    "actionRemovalError(QString,QString)\0"
    "actionRenamingSuccess(QString)\0"
    "actionRenamingError(QString,QString)\0"
    "_command\0actionTriggered(QString)\0"
    "connectionRemovalSuccess()\0_folder\0"
    "folderCreationSuccess(QString)\0"
    "_folder,_error\0folderCreationError(QString,QString)\0"
    "folderRemovalSuccess(QString)\0"
    "folderRemovalError(QString,QString)\0"
    "folderRenamingSuccess(QString)\0"
    "folderRenamingError(QString,QString)\0"
    "_uuid\0uuidRegistrationSuccess(QString)\0"
    "uuidDeregistrationSucess(QString)\0"
    "_uuid,_values\0"
    "appMessageReceived(QString,QHash<QString,QVariant>)\0"
    "appStarted(QString)\0appClosed(QString)\0"
    "_id\0dismissReceived(QString)\0_id,_text\0"
    "genericReceived(QString,QString)\0"
    "responseReceived(QString,QString)\0"
    "_data\0onDataReived(QString)\0"
    "onTalk2WatchLookup()\0bool\0"
    "isTalk2WatchInstalled()\0"
    "isTalk2WatchProInstalled()\0"
    "isTalk2WatchProServiceInstalled()\0"
    "_sender,_text\0sendSms(QString,QString)\0"
    "_sender,_subject,_text\0"
    "sendEmail(QString,QString,QString)\0"
    "_appName,_appVersion,_appKey,_protocol,_port,_description\0"
    "setAppValues(QString,QString,QString,QString,QString,QString)\0"
    "sendAppAuthorizationRequest()\0"
    "_title,_command,_description\0"
    "createAction(QString,QString,QString)\0"
    "_title,_folder,_command,_description\0"
    "createAction(QString,QString,QString,QString)\0"
    "_title\0createFolder(QString)\0"
    "_title,_parentFolder\0createFolder(QString,QString)\0"
    "removeConnection()\0removeAction(QString)\0"
    "removeFolder(QString)\0_oldTitle,_newTitle\0"
    "renameAction(QString,QString)\0"
    "renameFolder(QString,QString)\0"
    "forwardSourceCode()\0"
    "sendAppMessage(QString,QHash<QString,QVariant>)\0"
    "sendAppLaunchRequest(QString)\0"
    "registerAppMessageListener(QString)\0"
    "deregisterAppMessageListener(QString)\0"
};

void Talk2WatchInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Talk2WatchInterface *_t = static_cast<Talk2WatchInterface *>(_o);
        switch (_id) {
        case 0: _t->transmissionReady(); break;
        case 1: _t->receivedData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->authSuccess(); break;
        case 3: _t->authError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->actionCreationSuccess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->actionCreationError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->actionRemovalSuccess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->actionRemovalError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->actionRenamingSuccess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->actionRenamingError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->actionTriggered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->connectionRemovalSuccess(); break;
        case 12: _t->folderCreationSuccess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->folderCreationError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->folderRemovalSuccess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->folderRemovalError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 16: _t->folderRenamingSuccess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->folderRenamingError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 18: _t->uuidRegistrationSuccess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: _t->uuidDeregistrationSucess((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->appMessageReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[2]))); break;
        case 21: _t->appStarted((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->appClosed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->dismissReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->genericReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 25: _t->responseReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 26: _t->onDataReived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 27: _t->onTalk2WatchLookup(); break;
        case 28: { bool _r = _t->isTalk2WatchInstalled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 29: { bool _r = _t->isTalk2WatchProInstalled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 30: { bool _r = _t->isTalk2WatchProServiceInstalled();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 31: _t->sendSms((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 32: _t->sendEmail((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 33: _t->setAppValues((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 34: _t->sendAppAuthorizationRequest(); break;
        case 35: _t->createAction((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 36: _t->createAction((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 37: _t->createFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 38: _t->createFolder((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 39: _t->removeConnection(); break;
        case 40: _t->removeAction((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: _t->removeFolder((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 42: _t->renameAction((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 43: _t->renameFolder((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 44: _t->forwardSourceCode(); break;
        case 45: _t->sendAppMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[2]))); break;
        case 46: _t->sendAppLaunchRequest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 47: _t->registerAppMessageListener((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 48: _t->deregisterAppMessageListener((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Talk2WatchInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Talk2WatchInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Talk2WatchInterface,
      qt_meta_data_Talk2WatchInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Talk2WatchInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Talk2WatchInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Talk2WatchInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Talk2WatchInterface))
        return static_cast<void*>(const_cast< Talk2WatchInterface*>(this));
    return QObject::qt_metacast(_clname);
}

int Talk2WatchInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    }
    return _id;
}

// SIGNAL 0
void Talk2WatchInterface::transmissionReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Talk2WatchInterface::receivedData(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Talk2WatchInterface::authSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Talk2WatchInterface::authError(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Talk2WatchInterface::actionCreationSuccess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Talk2WatchInterface::actionCreationError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Talk2WatchInterface::actionRemovalSuccess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Talk2WatchInterface::actionRemovalError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Talk2WatchInterface::actionRenamingSuccess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Talk2WatchInterface::actionRenamingError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Talk2WatchInterface::actionTriggered(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Talk2WatchInterface::connectionRemovalSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void Talk2WatchInterface::folderCreationSuccess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Talk2WatchInterface::folderCreationError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void Talk2WatchInterface::folderRemovalSuccess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void Talk2WatchInterface::folderRemovalError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void Talk2WatchInterface::folderRenamingSuccess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void Talk2WatchInterface::folderRenamingError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void Talk2WatchInterface::uuidRegistrationSuccess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void Talk2WatchInterface::uuidDeregistrationSucess(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void Talk2WatchInterface::appMessageReceived(const QString & _t1, const QHash<QString,QVariant> & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void Talk2WatchInterface::appStarted(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void Talk2WatchInterface::appClosed(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void Talk2WatchInterface::dismissReceived(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void Talk2WatchInterface::genericReceived(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void Talk2WatchInterface::responseReceived(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}
QT_END_MOC_NAMESPACE
