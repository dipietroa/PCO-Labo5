#ifndef WAITINGLOGGER_H
#define WAITINGLOGGER_H

#include <QStringList>
#include <QList>
#include <QMutex>
#include <stdexcept>
#include <iostream>

class WaitingQueue
{
private:
    QString name;
    QStringList threadNames;

public:
    WaitingQueue(QString name);
    void addThread(const QString& objectName);
    bool deleteThread(const QString& objectName);
    const QString getOName();
    QString getThreadsName();
};

class WaitingLogger
{
public:

    /**
     * @brief getInstance Returns the singleton
     * @return the only instance of WaitingLogger
     * This logger has to be a singleton, accessed by every synchronization
     * object
     */
    static WaitingLogger *getInstance();


    void addWaiting(const QString& threadName,const QString& objectName);

    void removeWaiting(const QString& threadName,const QString& objectName);



protected:
    WaitingLogger();

    QList<WaitingQueue *> getQueues() const;

    /**
     * @brief updateView Responsible for updating the view
     * This function should do what is required to update the view.
     * In this first version it could simply modify the display in
     * the terminal.
     */
    virtual void updateView();

    QList<WaitingQueue *> queues;

private:
    WaitingQueue* getQueueByObjName(const QString& objectName);
    QMutex mutex;

};

class ReadWriteLogger : public WaitingLogger
{
    friend WaitingLogger;

public:

    QStringList getResourceAccesses() const;

    void addResourceAccess(const QString &threadName);
    void removeResourceAccess(const QString &threadName);

protected:

    ReadWriteLogger();

    /**
     * @brief updateView Responsible for updating the view
     * This function should do what is required to update the view.
     * In this first version it could simply modify the display in
     * the terminal.
     */
    virtual void updateView();

    QStringList resourceAccesses;
private:
    QMutex mutexAccess;

};

#endif // WAITINGLOGGER_H
