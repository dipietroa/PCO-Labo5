#include "readerwriterequalpriomesa.h"

ReaderWriterEqualPrioMesa::ReaderWriterEqualPrioMesa() :
    mutex("mutex"),
    attenteA("attenteA"),
    attenteB("attenteB"),
    nbAttenteA(0),
    nbAttenteB(0),
    nbA(0),
    nbB(0) {
}

void ReaderWriterEqualPrioMesa::lockReading() {
    SynchroController::getInstance()->pause();
    mutex.lock();
    if (nbB > 0) {
        nbAttenteA ++;
        attenteA.wait(&mutex);
    }
    else
        nbA ++;
    mutex.unlock();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterEqualPrioMesa::unlockReading() {
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.lock();
    nbA --;
    if (nbA == 0) {
        attenteB.wakeAll();
        nbB = nbAttenteB;
        nbAttenteB = 0;
    }
    mutex.unlock();
}

void ReaderWriterEqualPrioMesa::lockWriting() {
    SynchroController::getInstance()->pause();
    mutex.lock();
    if (nbA > 0) {
        nbAttenteB ++;
        attenteB.wait(&mutex);
    }
    else
        nbB ++;
    mutex.unlock();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterEqualPrioMesa::unlockWriting() {
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.lock();
    nbB --;
    if (nbB == 0) {
        attenteA.wakeAll();
        nbA = nbAttenteA;
        nbAttenteA = 0;
    }
    mutex.unlock();
}
