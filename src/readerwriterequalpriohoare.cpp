#include "readerwriterequalpriohoare.h"

ReaderWriterEqualPrioHoare::ReaderWriterEqualPrioHoare() :
    hoaremonitor("waitMonitor"),
    nbA(0),
    nbB(0) {
}

void ReaderWriterEqualPrioHoare::lockReading() {
    hoaremonitor.monitorIn();
    if (nbB > 0) {
        hoaremonitor.wait(attenteA);
        hoaremonitor.signal(attenteA);
    }
    nbA ++;
    hoaremonitor.monitorOut();
}

void ReaderWriterEqualPrioHoare::unlockReading() {
    hoaremonitor.monitorIn();
    nbA --;
    if (nbA == 0)
        hoaremonitor.signal(attenteB);
    hoaremonitor.monitorOut();
}

void ReaderWriterEqualPrioHoare::lockWriting() {
    hoaremonitor.monitorIn();
    if (nbA > 0) {
        hoaremonitor.wait(attenteB);
        hoaremonitor.signal(attenteB);
    }
    nbB ++;
    hoaremonitor.monitorOut();
}

void ReaderWriterEqualPrioHoare::unlockWriting() {
    hoaremonitor.monitorIn();
    nbB --;
    if (nbB == 0)
        hoaremonitor.signal(attenteA);
    hoaremonitor.monitorOut();
}
