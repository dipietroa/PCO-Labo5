#ifndef PSEMAPHORE_H
#define PSEMAPHORE_H
#include <QString>
#include <QSemaphore>
#include <QThread>
#include "waitinglogger.h"

class OSemaphore
{
public:
    OSemaphore(int n = 0, QString name = "");

    void acquire(int n = 0);

    void release(int n = 0);

    bool tryAcquire(int n = 0);
private:
    QString _name;
    QSemaphore* semaphore;

};

#endif // PSEMAPHORE_H
