#ifndef TASKRW_H
#define TASKRW_H

#include <iostream>
#include <QThread>
#include "abstractreaderwriter.h"
#include "waitinglogger.h"

/**
 * @brief Thread utilisant les méthodes réservées
 *        aux lecteurs dans les classes implémentant
 *        un des protocoles lecteur/rédacteur
 */
class TaskReader :public QThread{
private:
    AbstractReaderWriter* _protocol; //classe implémentant le protocole
public:
    /**
     * @brief run - boucle infinie (vérouille la lecture puis
     *        la dévérouille continuellement)
     */
    void run();

    /**
     * @brief Constructeur
     * @param protocol
     */
    TaskReader(AbstractReaderWriter* protocol);
};

/**
 * @brief Thread utilisant les méthodes réservées
 *        aux rédacteurs dans les classes implémentant
 *        un des protocoles lecteur/rédacteur
 */
class TaskWriter :public QThread{
private:
    AbstractReaderWriter* _protocol; //classe implémentant le protocole
public:
    /**
     * @brief run - boucle infinie (vérouille l'écriture puis
     *        la dévérouille continuellement)
     */
    void run();

    /**
     * @brief Constructeur
     * @param protocol
     */
    TaskWriter(AbstractReaderWriter* protocol);
};

#endif // TASKRW_H
