#ifndef READERWRITERPRIOREADERMESA_H
#define READERWRITERPRIOREADERMESA_H



#include "omutex.h"
#include "owaitcondition.h"
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

#include "osemaphore.h"
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

/**
 * @brief The ReaderWriterPrioReadersMesa class :
 * classe qui implémente un lecteur-redacteur avec priorité
 * aux rédacteurs à l'aide d'e semaphores'un moniteur de Mesa.
 */
class ReaderWriterPrioReaderMesa : public AbstractReaderWriter
{
public:
    /**
     * @brief ReaderWriterPrioReaderMesa constructeur de la classe
     */
    ReaderWriterPrioReaderMesa();

    /**
      * destructeur de la classe
      */
    ~ReaderWriterPrioReaderMesa();
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
protected:
    OMutex mutex;
    OWaitCondition readerBlocker;
    OWaitCondition writerBlocker;
    int nbReaders;
    int nbReadersWaiting;
    int nbWritersWaiting;
    bool oneWriter; //booléen qui détérmine si il y a un Writer

};

#endif // READERWRITERPRIOREADERMESA_H
