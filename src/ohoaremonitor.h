#ifndef OHOAREMONITOR_H
#define OHOAREMONITOR_H

#include <QString>
#include <QSemaphore>
#include <QMutex>
#include <QThread>
#include "waitinglogger.h"

class OHoareMonitor
{
public:
    class Condition
    {
        friend OHoareMonitor;
    public:
        Condition();
    private:
        QSemaphore waitingSem;
        int nbWaiting;
    };

    OHoareMonitor(QString name);

    /**
     * Cette fonction doit être appelée au début de chaque fonction étant
     * un point d'entrée du moniteur
     */
    void monitorIn();

    /**
     * Cette fonction doit être appelée à la fin de chaque fonction étant
     * un point d'entrée du moniteur
     */
    void monitorOut();

    /**
     * Cette fonction implémente l'attente sur une condition.
     * Lorsqu'un thread est réveillé par le signal, il continue
     * avec l'exclusion mutuelle
     */
    void wait(Condition &cond);

    /**
     * Cette fonction implémente le signal d'une condition. Si aucun thread attendait sur la condition,
     * alors rien ne se passe. Si ce n'est pas le cas, le thread appelant se suspend et attend la fin
     * de l'exécution du thread réveillé par le signal
     */
    void signal(Condition &cond);

private:
    QSemaphore monitorMutex;
    QSemaphore monitorSignale;
    int monitorNbSignale;
    QString _name;
};

#endif // OHOAREMONITOR_H
