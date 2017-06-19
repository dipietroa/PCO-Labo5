#include "readerwriterequalpriohoare.h"

ReaderWriterEqualPrioHoare::ReaderWriterEqualPrioHoare() :
    hoaremonitor("waitMonitor"),
    nbA(0),
    nbB(0) {
}

void ReaderWriterEqualPrioHoare::lockReading() {
    SynchroController::getInstance()->pause();
    hoaremonitor.monitorIn();
    if (nbB > 0) {
        hoaremonitor.wait(attenteA);
        hoaremonitor.signal(attenteA);
    }
    nbA ++;
    hoaremonitor.monitorOut();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterEqualPrioHoare::unlockReading() {
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    hoaremonitor.monitorIn();
    nbA --;
    if (nbA == 0)
        hoaremonitor.signal(attenteB);
    hoaremonitor.monitorOut();
}

void ReaderWriterEqualPrioHoare::lockWriting() {
    SynchroController::getInstance()->pause();
    hoaremonitor.monitorIn();
    if (nbA > 0) {
        hoaremonitor.wait(attenteB);
        hoaremonitor.signal(attenteB);
    }
    nbB ++;
    hoaremonitor.monitorOut();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterEqualPrioHoare::unlockWriting() {
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    hoaremonitor.monitorIn();
    nbB --;
    if (nbB == 0)
        hoaremonitor.signal(attenteA);
    hoaremonitor.monitorOut();
}
