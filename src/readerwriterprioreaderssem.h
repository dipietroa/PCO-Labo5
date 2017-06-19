#ifndef READERWRITERPRIOREADERS_H
#define READERWRITERPRIOREADERS_H

#include "osemaphore.h"
#include "abstractreaderwriter.h"

class ReaderWriterPrioReadersSem : public AbstractReaderWriter
{
public:
    ReaderWriterPrioReadersSem();
    void lockReading();
    void lockWriting();
    void unlockReading();
    void unlockWriting();
protected:
    OSemaphore mutexReaders;
    OSemaphore mutexWriters;
    OSemaphore writer;
    int nbReaders;
};

#endif // READERWRITERPRIOREADERS_H
