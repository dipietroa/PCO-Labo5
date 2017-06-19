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
    /**
     * @brief Constructeur
     * @param name
     */
    WaitingQueue(QString name);

    /**
     * @brief addThread - ajoute un thread à la file d'attente
     * @param objectName
     */
    void addThread(const QString& objectName);

    /**
     * @brief deleteThread - supprime un thread de la file d'attente
     * @param objectName
     * @return
     */
    bool deleteThread(const QString& objectName);

    /**
     * @brief getOName - retourne le nom de l'objet de synchronisation
     *        auquel est lié la file
     * @return
     */
    const QString getOName();

    /**
     * @brief getThreadsName - récupère le nom des threads en attente
     *        sur l'objet de synchronisation
     * @return
     */
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


    /**
     * @brief addWaiting - référence le thread qualifié par "threadName"
     *                     comme étant en attente sur l'objet de synchro
     *                     qualifié par "objectName"
     * @param threadName
     * @param objectName
     */
    void addWaiting(const QString& threadName,const QString& objectName);


    /**
     * @brief addWaiting - supprime la référence du thread qualifié par "threadName"
     *                     de la liste d'attente sur l'objet qualifié par "objectName"
     * @param threadName
     * @param objectName
     */
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
    /**
     * @brief getQueueByObjName - Récupère la file d'attente de l'objet de
     *                            synchro "objectName"
     * @param objectName
     * @return
     */
    WaitingQueue* getQueueByObjName(const QString& objectName);
    QMutex mutex;

};

class ReadWriteLogger : public WaitingLogger
{
    friend WaitingLogger;

public:

    QStringList getResourceAccesses() const;

    /**
     * @brief addResourceAccess - Référence le thread "threadName" comme ayant
     *                            accès à la ressource
     * @param threadName
     */
    void addResourceAccess(const QString &threadName);

    /**
     * @brief removeResourceAccess - Supprime la référence disant que "threadName"
     *                               a accès à la ressource
     * @param threadName
     */
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
