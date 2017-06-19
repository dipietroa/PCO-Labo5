#include "waitinglogger.h"
#include <stdexcept>

WaitingQueue::WaitingQueue(QString name) : name(name), threadNames(){}

void WaitingQueue::addThread(const QString &objectName){
    threadNames.push_back(objectName);
}

bool WaitingQueue::deleteThread(const QString &objectName){
    return threadNames.removeOne(objectName);
}

const QString WaitingQueue::getOName(){
    return name;
}

WaitingLogger::WaitingLogger()
{

}

WaitingLogger *WaitingLogger::getInstance()
{
    static WaitingLogger *instance = new ReadWriteLogger();
    return instance;
}

QList<WaitingQueue *> WaitingLogger::getQueues() const
{
    return queues;
}

void WaitingLogger::updateView()
{
    //code affichage
}

void WaitingLogger::addWaiting(const QString &threadName, const QString &objectName){
    WaitingQueue* wq = getQueueByObjName(objectName);
    if(wq != nullptr)
        wq->addThread(threadName);
    else{
        wq = new WaitingQueue(objectName);
        wq->addThread(threadName);
        queues.push_back(wq);
    }
}

void WaitingLogger::removeWaiting(const QString &threadName, const QString &objectName){
    WaitingQueue* wq = getQueueByObjName(objectName);
    if(wq != nullptr)
        if(wq->deleteThread(threadName))
            throw new std::runtime_error("Erreur, le thread '" +threadName.toStdString() +
                                         "' n'est pas en attente sur '" + objectName.toStdString() +"' !");
}

WaitingQueue* WaitingLogger::getQueueByObjName(const QString &objectName){
    for(auto i = queues.begin(); i != queues.end(); i++){
        if((*i)->getOName() == objectName)
            return *i;
    }
    return nullptr;
}

QStringList ReadWriteLogger::getResourceAccesses() const
{
    return resourceAccesses;
}

ReadWriteLogger::ReadWriteLogger()
{

}

void ReadWriteLogger::addResourceAccess(const QString &threadName)
{
    resourceAccesses.push_back(threadName);
}

void ReadWriteLogger::removeResourceAccess(const QString &threadName)
{
    if(resourceAccesses.removeOne(threadName))
       throw new std::runtime_error("Le thread " +threadName.toStdString() + " n'est pas entrain d'accéder à la ressource.");
}


void ReadWriteLogger::updateView()
{
    WaitingLogger::updateView();
    //Code affichage
}
