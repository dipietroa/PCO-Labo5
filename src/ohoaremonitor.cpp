#include "ohoaremonitor.h"

OHoareMonitor::Condition::Condition() : waitingSem(0), nbWaiting(0) {}

OHoareMonitor::OHoareMonitor(QString name) : _name(name), monitorMutex(1), monitorSignale(0), monitorNbSignale(0) {}

void OHoareMonitor::monitorIn() {
    monitorMutex.acquire();
}

void OHoareMonitor::monitorOut() {
    if (monitorNbSignale > 0)
        monitorSignale.release();
    else
        monitorMutex.release();
}

void OHoareMonitor::wait(Condition &cond) {
    QString tName = QThread::currentThread()->objectName();
    WaitingLogger::getInstance()->addWaiting(tName, _name);

    cond.nbWaiting += 1;
    if (monitorNbSignale > 0)
        monitorSignale.release();
    else
        monitorMutex.release();

    cond.waitingSem.acquire();
    cond.nbWaiting -= 1;

    WaitingLogger::getInstance()->removeWaiting(tName, _name);
}

void OHoareMonitor::signal(Condition &cond) {
    if (cond.nbWaiting>0) {
        monitorNbSignale += 1;
        cond.waitingSem.release();
        monitorSignale.acquire();
        monitorNbSignale -= 1;
    }
}
