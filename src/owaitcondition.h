#ifndef PWAITCONDITION_H
#define PWAITCONDITION_H

#include <QWaitCondition>
#include <QString>
#include "omutex.h"

class OWaitCondition : public QWaitCondition
{
public:
    OWaitCondition(QString name);

    bool wait(OMutex *lockedMutex);

    void wakeAll();

    void wakeOne();

private:
    QWaitCondition* _qwcond;
    QString _name;

};

#endif // PWAITCONDITION_H
