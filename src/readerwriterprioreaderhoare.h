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

    /**
     * @brief lockReading : méthode qui bloque la lecture
     */
    void lockReading();
    /**
     * @brief lockWriting : méthode qui bloque l'écriture
     */
    void lockWriting();
    /**
     * @brief unlockReading méthode qui débloque la lecture
     */
    void unlockReading();
    /**
     * @brief unlockWriting méthode qui débloque l'écriture
     */
    void unlockWriting();
};

#endif // READERWRITERPRIOREADERHOARE_H
