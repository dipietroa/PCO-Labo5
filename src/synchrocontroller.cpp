#include "synchrocontroller.h"

SynchroController::SynchroController() : mutex(), qwcond()
{

}


SynchroController *SynchroController::getInstance()
{
    static SynchroController *instance = new SynchroController();
    return instance;
}

void SynchroController::pause()
{
    mutex.lock();
    qwcond.wait(&mutex);
    mutex.unlock();
}

void SynchroController::resume()
{
    mutex.lock();
    qwcond.wakeAll();
    mutex.unlock();
}
