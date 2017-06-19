#include "readerwriterprioreaderhoare.h"

ReaderWriterPrioReaderHoare::ReaderWriterPrioReaderHoare() :
    hoaremonitor("waitMonitor"),
    nbReaders(0),
    oneWriter(false){
}

void ReaderWriterPrioReaderHoare::lockReading() {
    SynchroController::getInstance()->pause();
    hoaremonitor.monitorIn();

    if (oneWriter) {// si il y a un Redacteur
        hoaremonitor.wait(readerBlocker);
        hoaremonitor.signal(readerBlocker);
    }
    else { {// sinon un lecteur en plus
        nbReaders++;
        hoaremonitor.monitorOut();
    }

    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
    }
}
void ReaderWriterPrioReaderHoare::lockWriting(){
    SynchroController::getInstance()->pause();
    hoaremonitor.monitorIn();
    if (oneWriter || (nbReaders>0)) {//si aucun redacteur ou s'il y a des lecteurs

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
    if (nbReaders>0)//s'il y a des lecteurs
    {
             hoaremonitor.signal(readerBlocker);
    }
    else {
            oneWriter=true;
            hoaremonitor.wait(writerBlocker);
            hoaremonitor.signal(writerBlocker);
    }
    hoaremonitor.monitorOut();
}

