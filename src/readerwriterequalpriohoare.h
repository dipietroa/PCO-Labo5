#ifndef READERWRITEREQUALPRIOHOARE_H
#define READERWRITEREQUALPRIOHOARE_H

#include "ohoaremonitor.h"
#include "abstractreaderwriter.h"

class ReaderWriterEqualPrioHoare : public AbstractReaderWriter
{
protected:
    OHoareMonitor::Condition attenteA;
    OHoareMonitor::Condition attenteB;
    OHoareMonitor hoaremonitor;

    int nbA;
    int nbB;

public:
    ReaderWriterEqualPrioHoare();

    void lockReading();

    void unlockReading();

    void lockWriting();

    void unlockWriting();
};

#endif // READERWRITEREQUALPRIOHOARE_H
