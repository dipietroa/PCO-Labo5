#include "omutex.h"

OMutex::OMutex(QString name) : name(name), mutex(new QMutex()){}

void OMutex::lock(){
    QString tName = QThread::currentThread()->objectName();
    WaitingLogger::getInstance()->addWaiting(tName, name);
    mutex->lock();
    WaitingLogger::getInstance()->removeWaiting(tName, name);
}

void OMutex::unlock(){
    mutex->unlock();
}

bool OMutex::tryLock(){
    QString tName = QThread::currentThread()->objectName();
    WaitingLogger::getInstance()->addWaiting(tName, name);
    bool isLocked = mutex->tryLock();
    WaitingLogger::getInstance()->removeWaiting(tName, name);
    return isLocked;
}
