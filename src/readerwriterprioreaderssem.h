#ifndef READERWRITERPRIOREADERS_H
#define READERWRITERPRIOREADERS_H

#include "osemaphore.h"
#include "abstractreaderwriter.h"

class ReaderWriterPrioReadersSem : public AbstractReaderWriter
{
public:
    ReaderWriterPrioReadersSem();
    ~ReaderWriterPrioReadersSem();
    void lockReading();
    void lockWriting();
    void unlockReading();
    void unlockWriting();
protected:
    OSemaphore mutex;
    OSemaphore readerBlocker;
    OSemaphore writerBlocker;
    int nbReaders;
    int nbReadersWaiting;
    int nbWritersWaiting;
    bool oneWriter;

};

#endif // READERWRITERPRIOREADERS_H
