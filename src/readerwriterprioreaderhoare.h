#ifndef READERWRITERPRIOREADERHOARE_H
#define READERWRITERPRIOREADERHOARE_H


class ReaderWriterPrioReaderHoare
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
