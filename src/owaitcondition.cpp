#include "owaitcondition.h"

OWaitCondition::OWaitCondition(QString name) : _name(name), _qwcond(new QWaitCondition()){}

void OWaitCondition::wait(OMutex *lockedMutex){
    QString tName = QThread::currentThread()->objectName();
    WaitingLogger::getInstance()->addWaiting(tName, _name);
    _qwcond->wait(lockedMutex);
    WaitingLogger::getInstance()->removeWaiting(tName, _name);
}

void OWaitCondition::wakeOne(){
   _qwcond->wakeOne();
}

void OWaitCondition::wakeAll(){
   _qwcond->wakeAll();
}
