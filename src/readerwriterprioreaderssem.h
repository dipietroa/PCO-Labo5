#ifndef READERWRITERPRIOREADERS_H
#define READERWRITERPRIOREADERS_H

#include "osemaphore.h"
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"
/**
 * @brief The ReaderWriterPrioReadersSem class :
 * classe qui implémente un lecteur-redacteur avec priorité
 * aux rédacteurs à l'aide de semaphores.
 */
class ReaderWriterPrioReadersSem : public AbstractReaderWriter
{
public:
    /**
     * @brief ReaderWriterPrioReadersSem constructeur de la classe
     */
    ReaderWriterPrioReadersSem();

    /**
     *destructeur de la classe
     */
    ~ReaderWriterPrioReadersSem();

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
    OSemaphore mutex; //exclusion mutuelle
    OSemaphore readerBlocker; //semaphore pour attente des lecteurs
    OSemaphore writerBlocker; //semaphore pour l attente des redacteurs
    int nbReaders; // nombre de lecteur actifs
    int nbReadersWaiting; //nombre de lecteur en attente
    int nbWritersWaiting; // nombre de redacteurs en attente
    bool oneWriter; //booléen qui détérmine si il y a un Writer

};

#endif // READERWRITERPRIOREADERS_H
