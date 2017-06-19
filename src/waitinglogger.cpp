#include "waitinglogger.h"

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

QString WaitingQueue::getThreadsName(){
    QString str;
    for(QString s : threadNames)
        str.append(QString::fromStdString(s.toStdString() + ", "));
     return str;
}

WaitingLogger::WaitingLogger() : mutex()
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
    for(WaitingQueue* wq : queues){
        std::cout << wq->getOName().toStdString() << " : "
                  << wq->getThreadsName().toStdString()
                  << std::endl;
    }
}

void WaitingLogger::addWaiting(const QString &threadName, const QString &objectName){
    mutex.lock();
    WaitingQueue* wq = getQueueByObjName(objectName);
    if(wq != nullptr)
        wq->addThread(threadName);
    else{
        wq = new WaitingQueue(objectName);
        wq->addThread(threadName);
        queues.push_back(wq);
    }
    updateView();
    mutex.unlock();
}

void WaitingLogger::removeWaiting(const QString &threadName, const QString &objectName){
    mutex.lock();
    WaitingQueue* wq = getQueueByObjName(objectName);
    if(wq != nullptr)
        if(!wq->deleteThread(threadName))
            throw new std::runtime_error("Erreur, le thread '" +threadName.toStdString() +
                                         "' n'est pas en attente sur '" + objectName.toStdString() +"' !");
    updateView();
    mutex.unlock();
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

ReadWriteLogger::ReadWriteLogger() : mutexAccess()
{

}

void ReadWriteLogger::addResourceAccess(const QString &threadName)
{
    mutexAccess.lock();
    resourceAccesses.push_back(threadName);
    mutexAccess.unlock();
}

void ReadWriteLogger::removeResourceAccess(const QString &threadName)
{
    mutexAccess.lock();
    if(!resourceAccesses.removeOne(threadName))
       throw new std::runtime_error("Le thread " +threadName.toStdString() + " n'est pas entrain d'accéder à la ressource.");
    mutexAccess.unlock();
}


void ReadWriteLogger::updateView()
{
    WaitingLogger::updateView();
    std::cout << "In resource : ";
    for(QString s : resourceAccesses){
        std::cout << s.toStdString() << ", ";
    }
    std::cout << std::endl << std::endl;
}
