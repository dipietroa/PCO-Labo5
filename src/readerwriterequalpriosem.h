#ifndef READERWRITEREQUALPRIOSEM_H
#define READERWRITEREQUALPRIOSEM_H
#include "abstractreaderwriter.h"
#include "osemaphore.h"
#include "synchrocontroller.h"

/**
 * @brief Classe implémentant le protocole lecteur rédacteur
 *        avec priorité égale en utilisant des semaphores
 *        pour la gestion de l'exclusion mutuelle
 *
 *        cette solution avait été réalisée dans le cadre d'un
 *        exercice en cours (exercie 20)
 */
class ReaderWriterEqualPrioSem : public AbstractReaderWriter
{
protected:
    OSemaphore mutex; //Semaphore initialisé à 1 (comportement mutex)
                      //pour l'exclusion mutuelle

    OSemaphore attenteA; //semaphore pour l'attente des lecteurs
    int nbAttenteA; //nombre de lecteurs en attente

    OSemaphore attenteB; //semaphore pour l'attente des rédacteurs
    int nbAttenteB; //nombre de rédacteurs en attente

    int nbA; //nb lecteurs
    int nbB; //nb redacteurs

public:
    /**
     * @brief Constructeur
     */
    ReaderWriterEqualPrioSem();

    /**
     * @brief override lockReading
     */
    void lockReading();

    /**
     * @brief override unlockReading
     */
    void unlockReading();

    /**
     * @brief override lockWriting
     */
    void lockWriting();

    /**
     * @brief override unlockWriting
     */
    void unlockWriting();
};

#endif // READERWRITEREQUALPRIOSEM_H
