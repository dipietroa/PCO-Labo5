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
    mutex.lock();
    if (nbB > 0) {
        nbAttenteA ++;
        attenteA.wait(&mutex);
    }
    else
        nbA ++;
    mutex.unlock();
}

void ReaderWriterEqualPrioMesa::unlockReading() {
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
    mutex.lock();
    if (nbA > 0) {
        nbAttenteB ++;
        attenteB.wait(&mutex);
    }
    else
        nbB ++;
    mutex.unlock();

}

void ReaderWriterEqualPrioMesa::unlockWriting() {
    mutex.lock();
    nbB --;
    if (nbB == 0) {
        attenteA.wakeAll();
        nbA = nbAttenteA;
        nbAttenteA = 0;
    }
    mutex.unlock();
}
