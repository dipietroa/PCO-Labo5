#ifndef READERWRITEREQUALPRIOMESA_H
#define READERWRITEREQUALPRIOMESA_H

#include "omutex.h"
#include "owaitcondition.h"
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

/**
 * @brief Classe implémentant le protocole lecteur rédacteur
 *        avec priorité égale en utilisant un moniteur de mesa
 *        pour la gestion de l'exclusion mutuelle
 *
 *        cette solution avait été réalisée dans le cadre d'un
 *        exercice en cours (exercie 20)
 */
class ReaderWriterEqualPrioMesa : public AbstractReaderWriter
{
protected:
    OMutex mutex; //mutex utilisé pour l'exclusion mutelle
    OWaitCondition attenteA; //Wait condition pour lecteur
    int nbAttenteA; //nb thread lecteurs en attente
    OWaitCondition attenteB; //Wait condition pour rédacteur
    int nbAttenteB; //nb thread rédacteurs en attente
    int nbA; //nb threads lecteurs
    int nbB; //nb threads rédacteurs

public:
    /**
     * @brief Constructeur
     */
    ReaderWriterEqualPrioMesa();

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

#endif // READERWRITEREQUALPRIOMESA_H
