#ifndef READERWRITEREQUALPRIOSEM_H
#define READERWRITEREQUALPRIOSEM_H
#include "abstractreaderwriter.h"
#include "osemaphore.h"

class ReaderWriterEqualPrioSem : public AbstractReaderWriter
{
protected:
    OSemaphore mutex;

    OSemaphore attenteA;
    int nbAttenteA;

    OSemaphore attenteB;
    int nbAttenteB;

    int nbA;
    int nbB;

public:
    ReaderWriterEqualPrioSem();

    void lockReading();

    void unlockReading();

    void lockWriting();

    void unlockWriting();
};

#endif // READERWRITEREQUALPRIOSEM_H
