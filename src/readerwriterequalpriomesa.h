#ifndef READERWRITEREQUALPRIOMESA_H
#define READERWRITEREQUALPRIOMESA_H

#include "omutex.h"
#include "owaitcondition.h"
#include "abstractreaderwriter.h"

class ReaderWriterEqualPrioMesa : public AbstractReaderWriter
{
protected:
    OMutex mutex;
    OWaitCondition attenteA;
    int nbAttenteA;
    OWaitCondition attenteB;
    int nbAttenteB;
    int nbA;
    int nbB;

public:
    ReaderWriterEqualPrioMesa();

    void lockReading();

    void unlockReading();

    void lockWriting();

    void unlockWriting();
};

#endif // READERWRITEREQUALPRIOMESA_H
