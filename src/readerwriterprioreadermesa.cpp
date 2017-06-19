#include "readerwriterprioreadermesa.h"

ReaderWriterPrioReaderMesa::ReaderWriterPrioReaderMesa() :
    mutex("mutex"),
    nbReaders(0),
    nbReadersWaiting(0),
    nbWritersWaiting(0),
    readerBlocker("readerBlocker"),
    writerBlocker("writerBlocker"),
    oneWriter(false) {}

ReaderWriterPrioReaderMesa::~ReaderWriterPrioReaderMesa(){}

void ReaderWriterPrioReaderMesa::lockReading() {
    SynchroController::getInstance()->pause();
    mutex.lock();

    if (oneWriter) {// si il y a un Redacteur
        nbReadersWaiting++; // on ajoute un lecteur a l'attente
        readerBlocker.wait(&mutex);
    }
    else {// sinon un lecteur en plus
        nbReaders++;
        mutex.unlock();
    }

    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReaderMesa::lockWriting(){
    SynchroController::getInstance()->pause();
    mutex.lock();

        // s'il y a un redacteur ou au moins 1 lecteur ou des lecteurs en attente
    if (oneWriter || (nbReaders>0) || (nbReadersWaiting>0)) {
        nbWritersWaiting++; // le redacteur se met en attente
        writerBlocker.wait(&mutex);
    }
    else { // sinon il y a un redacteur
        oneWriter=true;
        mutex.unlock();
    }
    ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
}

void ReaderWriterPrioReaderMesa::unlockReading(){
    SynchroController::getInstance()->pause();
    ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
    mutex.lock();
    nbReaders--; //un lecteur en moins
    if (nbReaders==0) { //si plus aucun lecteur
        if (nbWritersWaiting>0) { // si il y a des redacteur en attente on ajoute un de redacteur
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
    oneWriter=false; //vu que c est priorité au lecteur, on remet tout de suite oneWriter a false
    if (nbReadersWaiting>0)// si il y a des lecteurs en attente
    {
            readerBlocker.wakeAll(); // on relase tous les lecteur en attente, ils peuvent y aller en meme temps
        nbReaders=nbReadersWaiting;
        nbReadersWaiting=0;
    }
    else { // si il n y a pas de lecteur en attente
        if (nbWritersWaiting>0) {// et qu il y a des redacteur on en ajoute 1
            oneWriter=true;
            nbWritersWaiting--;
            writerBlocker.wait(&mutex);
        }
    }
    mutex.unlock();
}
