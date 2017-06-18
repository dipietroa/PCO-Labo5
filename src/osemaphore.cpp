#include "osemaphore.h"

OSemaphore::OSemaphore(int n, QString name) : semaphore(new QSemaphore(n)), _name(name){}

void OSemaphore::acquire(int n){
    QString tName = QThread::currentThread()->objectName();
    WaitingLogger::getInstance()->addWaiting(tName, _name);
    semaphore->acquire(n);
    WaitingLogger::getInstance()->removeWaiting(tName, _name);
}

void OSemaphore::release(int n){
    semaphore->release(n);
}

bool OSemaphore::tryAcquire(int n){
    QString tName = QThread::currentThread()->objectName();
    WaitingLogger::getInstance()->addWaiting(tName, _name);
    bool success = semaphore->tryAcquire(n);
    WaitingLogger::getInstance()->removeWaiting(tName, _name);
    return success;
}
