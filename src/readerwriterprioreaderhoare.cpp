#include "readerwriterprioreaderhoare.h"

ReaderWriterPrioReaderHoare::ReaderWriterPrioReaderHoare() :
    hoaremonitor("waitMonitor"),
    nbReaders(0),
    oneWriter(false){
}

void ReaderWriterPrioReaderHoare::lockReading() {
    SynchroController::getInstance()->pause();
    hoaremonitor.monitorIn();

    if (oneWriter) {
        hoaremonitor.wait(readerBlocker);
        hoaremonitor.signal(readerBlocker);
    }
    else {
        nbReaders++;
        hoaremonitor.monitorOut();
    }

    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReaderHoare::lockWriting(){
    SynchroController::getInstance()->pause();
    hoaremonitor.monitorIn();
    if (oneWriter || (nbReaders>0)) {

        hoaremonitor.wait(writerBlocker);
        hoaremonitor.signal(writerBlocker);
    }
    else {
        oneWriter=true;
        hoaremonitor.monitorOut();
    }
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReaderHoare::unlockReading(){
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    hoaremonitor.monitorIn();
    nbReaders--;
    if (nbReaders==0)
    {
            oneWriter=true;
            hoaremonitor.wait(writerBlocker);
            hoaremonitor.signal(writerBlocker);
    }
    hoaremonitor.monitorOut();
}

void ReaderWriterPrioReaderHoare::unlockWriting(){
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    hoaremonitor.monitorIn();
    oneWriter=false;
    hoaremonitor.signal(readerBlocker);
    else {
            oneWriter=true;
            hoaremonitor.wait(writerBlocker);
            hoaremonitor.signal(writerBlocker);
    }
    hoaremonitor.monitorOut();
}

