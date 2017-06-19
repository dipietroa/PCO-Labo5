#include "readerwriterprioreaderssem.h"

ReaderWriterPrioReadersSem::ReaderWriterPrioReadersSem() :
  mutex(1, "mutex"),
  nbReaders(0),
  nbReadersWaiting(0),
  nbWritersWaiting(0),
  readerBlocker(0, "readerBlocker"),
  writerBlocker(0, "writerBlocker"),
  oneWriter(false) {}


ReaderWriterPrioReadersSem::~ReaderWriterPrioReadersSem(){

}

void ReaderWriterPrioReadersSem::lockReading(){
    mutex.acquire();

    if (oneWriter) {
        nbReadersWaiting++;
        mutex.release(); // ouverture
        readerBlocker.acquire();
    }
    else {
        nbReaders++;
        mutex.release();
    }

    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReadersSem::lockWriting(){
    mutex.acquire();
    if (oneWriter || (nbReaders>0) || (nbReadersWaiting>0)) {
        nbWritersWaiting++;
        mutex.release(); // ouverture
        writerBlocker.acquire();
    }
    else {
        oneWriter=true;
        mutex.release();
    }
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReadersSem::unlockReading(){
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.acquire();
    nbReaders--;
    if (nbReaders==0) {
        if (nbWritersWaiting>0) {
            oneWriter=true;
            nbWritersWaiting--;
            writerBlocker.release();
        }
    }
    mutex.release();
}

void ReaderWriterPrioReadersSem::unlockWriting(){
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.acquire();
    oneWriter=false;
    if (nbReadersWaiting>0) {
        for(int i=0;i<nbReadersWaiting;i++)
            readerBlocker.release();
        nbReaders=nbReadersWaiting;
        nbReadersWaiting=0;
    }
    else {
        if (nbWritersWaiting>0) {
            oneWriter=true;
            nbWritersWaiting--;
            writerBlocker.release();
        }
    }
    mutex.release();
}
