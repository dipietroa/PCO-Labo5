#ifndef PMUTEX_H
#define PMUTEX_H

#include <QThread>
#include <QMutex>
#include "waitinglogger.h"


/**
 * @brief Wrap QMutex pour gérer des logs
 *        permettant de connaître les threads
 *        en attente sur le mutex
 */
class OMutex : public QMutex
{

private:
    QString name;
    WaitingLogger *wl;
    QMutex* mutex;

public:
    /**
     * @brief Constructeur
     * @param name - nom du mutex
     */
    OMutex(QString name);

    /**
     * @brief lock - vérouille une section critique
     */
    void lock();

    /**
     * @brief tryLock - Tente de vérouiller une section critique
     * @return
     */
    bool tryLock();

    /**
     * @brief unlock - dévérouille une section critique
     */
    void unlock();
};

#endif // PMUTEX_H
