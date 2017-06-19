#ifndef PWAITCONDITION_H
#define PWAITCONDITION_H

#include <QWaitCondition>
#include <QString>
#include "omutex.h"

/**
 * @brief Classe wrap de QWaitCondition -> gestion de logs
 *        permettant de savoir qui est en attente sur la
 *        barrière
 */
class OWaitCondition : public QWaitCondition
{
public:
    /**
     * @brief Constructeur
     * @param nom de l'objet de syncronisation
     */
    OWaitCondition(QString name);

    /**
     * @brief wait - en attente d'un réveil
     * @param lockedMutex - mutex relâché
     * @return
     */
    bool wait(OMutex *lockedMutex);

    /**
     * @brief wakeAll - réveille tous les threads en attente
     */
    void wakeAll();

    /**
     * @brief wakeOne - réveille un thread en attente
     */
    void wakeOne();

private:
    QWaitCondition* _qwcond;
    QString _name;

};

#endif // PWAITCONDITION_H
