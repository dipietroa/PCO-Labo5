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
    SynchroController::getInstance()->pause();
    mutex.acquire();

    if (oneWriter) { // si il y a un Redacteur
        nbReadersWaiting++; // on ajoute un lecteur a l'attente
        mutex.release();
        readerBlocker.acquire();
    }
    else {
        nbReaders++; // sinon un lecteur en plus
        mutex.release();
    }

    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReadersSem::lockWriting(){
    SynchroController::getInstance()->pause();
    mutex.acquire();
    // s'il y a un redacteur ou au moins 1 lecteur ou des lecteurs en attente
    if (oneWriter || (nbReaders>0) || (nbReadersWaiting>0)) {
        nbWritersWaiting++; // le redacteur se met en attente
        mutex.release();
        writerBlocker.acquire();
    }
    else { // sinon il y a un redacteur
        oneWriter=true;
        mutex.release();
    }
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReadersSem::unlockReading(){
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.acquire();
    nbReaders--; //un lecteur en moins
    if (nbReaders==0) { //si plus aucun lecteur
        if (nbWritersWaiting>0) {// si il y a des redacteur en attente on ajoute un de redacteur
            oneWriter=true;
            nbWritersWaiting--;
            writerBlocker.release();
        }
    }
    mutex.release();
}

void ReaderWriterPrioReadersSem::unlockWriting(){
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.acquire();
    oneWriter=false; //vu que c est priorité au lecteur, on remet tout de suite oneWriter a false
    if (nbReadersWaiting>0) { // si il y a des lecteurs en attente
        for(int i=0;i<nbReadersWaiting;i++) // on relase tous les lecteur en attente, ils peuvent y aller en meme temps
            readerBlocker.release();
        nbReaders=nbReadersWaiting;
        nbReadersWaiting=0;
    }
    else { // si il n y a pas de lecteur en attente
        if (nbWritersWaiting>0) {// et qu il y a des redacteur on en ajoute 1
            oneWriter=true;
            nbWritersWaiting--;
            writerBlocker.release();
        }
    }
    mutex.release();
}
