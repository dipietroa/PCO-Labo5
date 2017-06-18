#include "owaitcondition.h"

OWaitCondition::OWaitCondition(QString name) : _name(name), _qwcond(new QWaitCondition()){}

bool OWaitCondition::wait(OMutex *lockedMutex){
    QString tName = QThread::currentThread()->objectName();
    WaitingLogger::getInstance()->addWaiting(tName, _name);
    bool success = _qwcond->wait(lockedMutex);
    WaitingLogger::getInstance()->removeWaiting(tName, _name);
    return success;
}

void OWaitCondition::wakeOne(){
   _qwcond->wakeOne();
}

void OWaitCondition::wakeAll(){
   _qwcond->wakeAll();
}
