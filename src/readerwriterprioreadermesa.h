#ifndef READERWRITERPRIOREADERMESA_H
#define READERWRITERPRIOREADERMESA_H



#include "omutex.h"
#include "owaitcondition.h"
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

#include "osemaphore.h"
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

class ReaderWriterPrioReaderMesa : public AbstractReaderWriter
{
public:
    ReaderWriterPrioReaderMesa();
    ~ReaderWriterPrioReaderMesa();
    void lockReading();
    void lockWriting();
    void unlockReading();
    void unlockWriting();
protected:
    OMutex mutex;
    OWaitCondition readerBlocker;
    OWaitCondition writerBlocker;
    int nbReaders;
    int nbReadersWaiting;
    int nbWritersWaiting;
    bool oneWriter;

};

#endif // READERWRITERPRIOREADERMESA_H
