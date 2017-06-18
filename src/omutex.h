#ifndef PMUTEX_H
#define PMUTEX_H

#include <QThread>
#include <QMutex>
#include "waitinglogger.h"


class OMutex : public QMutex
{

private:
    QString name;
    WaitingLogger *wl;
    QMutex* mutex;

public:
    OMutex(QString name);

    void lock();

    bool tryLock();

    void unlock();
};

#endif // PMUTEX_H
