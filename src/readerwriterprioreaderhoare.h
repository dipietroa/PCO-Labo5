#ifndef READERWRITERPRIOREADERHOARE_H
#define READERWRITERPRIOREADERHOARE_H
#include "ohoaremonitor.h"
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

class ReaderWriterPrioReaderHoare : public AbstractReaderWriter
{
protected:
    OHoareMonitor::Condition readerBlocker;
    OHoareMonitor::Condition writerBlocker;
    OHoareMonitor hoaremonitor;

    int nbReaders;
    bool oneWriter;

public:
    ReaderWriterPrioReaderHoare();

    void lockReading();

    void unlockReading();

    void lockWriting();

    void unlockWriting();
};

#endif // READERWRITERPRIOREADERHOARE_H
