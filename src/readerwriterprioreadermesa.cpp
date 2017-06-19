#include "readerwriterprioreadermesa.h"

ReaderWriterPrioReaderMesa::ReaderWriterPrioReaderMesa() :
    mutex("mutex"),
    readerBlocker("readerBlocker"),
    writerBlocker("writerBlocker"),
    nbReaders(0),
    nbReadersWaiting(0),
    nbWritersWaiting(0),
    oneWriter(false) {}

ReaderWriterPrioReaderMesa::~ReaderWriterPrioReaderMesa(){}

void ReaderWriterPrioReaderMesa::lockReading() {
    SynchroController::getInstance()->pause();
    mutex.lock();

    if (oneWriter) {
        nbReadersWaiting++;
        readerBlocker.wait(&mutex);
    }
    else {
        nbReaders++;
        mutex.unlock();
    }

    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReaderMesa::lockWriting(){
    SynchroController::getInstance()->pause();
    mutex.lock();
    if (oneWriter || (nbReaders>0) || (nbReadersWaiting>0)) {
        nbWritersWaiting++;
        writerBlocker.wait(&mutex);
    }
    else {
        oneWriter=true;
        mutex.unlock();
    }
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReaderMesa::unlockReading(){
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.lock();
    nbReaders--;
    if (nbReaders==0) {
        if (nbWritersWaiting>0) {
            oneWriter=true;
            nbWritersWaiting--;
            writerBlocker.wait(&mutex);
        }
    }
    mutex.unlock();
}

void ReaderWriterPrioReaderMesa::unlockWriting(){
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.lock();
    oneWriter=false;
    if (nbReadersWaiting>0)
    {
            readerBlocker.wakeAll();
        nbReaders=nbReadersWaiting;
        nbReadersWaiting=0;
    }
    else {
        if (nbWritersWaiting>0) {
            oneWriter=true;
            nbWritersWaiting--;
            writerBlocker.wait(&mutex);
        }
    }
    mutex.unlock();
}
