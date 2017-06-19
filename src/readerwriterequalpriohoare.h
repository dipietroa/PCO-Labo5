#ifndef READERWRITEREQUALPRIOHOARE_H
#define READERWRITEREQUALPRIOHOARE_H

#include "ohoaremonitor.h"
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

/**
 * @brief Classe implémentant le protocole lecteur rédacteur
 *        avec priorité égale en utilisant un moniteur de hoare
 *        pour la gestion de l'exclusion mutuelle
 *
 *        cette solution avait été réalisée dans le cadre d'un
 *        exercice en cours (exercie 20)
 */
class ReaderWriterEqualPrioHoare : public AbstractReaderWriter
{
protected:
    OHoareMonitor::Condition attenteA; //Condition d'attente pour lecteur
    OHoareMonitor::Condition attenteB; //Condition d'attente pour rédacteur
    OHoareMonitor hoaremonitor; //Moniteur

    int nbA; //nb threads lecteurs
    int nbB; //nb threads rédacteurs

public:
    ReaderWriterEqualPrioHoare();

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

#endif // READERWRITEREQUALPRIOHOARE_H
