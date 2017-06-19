#ifndef PSEMAPHORE_H
#define PSEMAPHORE_H
#include <QString>
#include <QSemaphore>
#include <QThread>
#include "waitinglogger.h"

/**
 * @brief Classe wrap de QSemaphore -
 *        gestion des logs pour connaître les
 *        threads en attente sur le semaphore
 */
class OSemaphore : public QSemaphore
{
public:
    /**
     * @brief Constructeur
     * @param n valeur initiale du semaphore
     * @param name nom de l'objet de synchro
     */
    OSemaphore(int n = 0, QString name = "");

    /**
     * @brief acquire - s'acquiert le semaphore
     * @param n
     */
    void acquire(int n = 0);

    /**
     * @brief release - relâche un thread en attente sur le semaphore
     * @param n
     */
    void release(int n = 0);

    /**
     * @brief tryAcquire - tente d'acquérir le semaphore
     * @param n
     * @return
     */
    bool tryAcquire(int n = 0);
private:
    QString _name;
    QSemaphore* semaphore;

};

#endif // PSEMAPHORE_H
