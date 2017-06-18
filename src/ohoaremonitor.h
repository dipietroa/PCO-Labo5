#ifndef OHOAREMONITOR_H
#define OHOAREMONITOR_H

#include <QString>
#include <QSemaphore>
#include <QMutex>
#include <QThread>
#include "waitinglogger.h"

class OHoareMonitor
{
protected:

    class Condition
    {
        friend OHoareMonitor;
    public:
        Condition();
    private:
        QSemaphore waitingSem;
        int nbWaiting;
    };

public:
    OHoareMonitor(QString name);

    /**
     * This function has to be called at the beginning of each function being
     * an entry point to the monitor.
     */
    void monitorIn();

    /**
     * This function has to be called at the end of each function being
     * an entry point to the monitor.
     */
    void monitorOut();

    /**
     * This function implements the waiting on a condition, as defined by Hoare.
     * When the thread is waken by a signal, it continues with the mutual
     * exclusion.
     */
    void wait(Condition &cond);

    /**
     * This function implements the signaling of a condition, as defined by
     * Hoare. If no thread is waiting for the condition, then nothing happens,
     * but if there is one the thread calling signal is suspended, waiting for
     * the other one to finish.
     */
    void signal(Condition &cond);

private:
    QSemaphore monitorMutex;
    QSemaphore monitorSignale;
    int monitorNbSignale;
    QString _name;
};

#endif // OHOAREMONITOR_H
