#include "readerwriterequalpriosem.h"

ReaderWriterEqualPrioSem::ReaderWriterEqualPrioSem() : mutex(1, "mutex"), attenteA(0, "attenteLecteur"), attenteB(0, "attenteRedacteur"),
                                                        nbAttenteA(0), nbAttenteB(0), nbA(0), nbB(0) {}

void ReaderWriterEqualPrioSem::lockReading() {
    mutex.acquire();
    if (nbB > 0) {
        nbAttenteA ++;
        mutex.release();
        attenteA.acquire();
    }
    else {
        nbA ++;
        mutex.release();
    }
}

void ReaderWriterEqualPrioSem::unlockReading() {
    mutex.acquire();
    nbA --;
    if (nbA == 0) {
        for(int i=0;i < nbAttenteB ; i++)
            attenteB.release();
        nbB = nbAttenteB;
        nbAttenteB = 0;
    }
    mutex.release();
}

void ReaderWriterEqualPrioSem::lockWriting() {
    mutex.acquire();
    if (nbA > 0) {
        nbAttenteB ++;
        mutex.release();
        attenteB.acquire();
    }
    else {
        nbB ++;
        mutex.release();
    }

}

void ReaderWriterEqualPrioSem::unlockWriting() {
    mutex.acquire();
    nbB --;
    if (nbB == 0) {
        for(int i=0;i < nbAttenteA ; i++)
            attenteA.release();
        nbA = nbAttenteA;
        nbAttenteA = 0;
    }
    mutex.release();
}
