#ifndef SYNCHROCONTROLLER_H
#define SYNCHROCONTROLLER_H

#include <QWaitCondition>
#include <QMutex>

class SynchroController
{
    SynchroController();
public:
    static SynchroController *getInstance();

    void pause();

    void resume();
private:
    QWaitCondition qwcond;
    QMutex mutex;
};

#endif // SYNCHROCONTROLLER_H
