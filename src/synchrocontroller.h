#ifndef SYNCHROCONTROLLER_H
#define SYNCHROCONTROLLER_H

#include <QWaitCondition>
#include <QMutex>


class SynchroController
{
    SynchroController();
public:
    static SynchroController *getInstance();

    /**
     * @brief pause - synchronisation des threads sur une
     *                QWaitCondition pour que l'utilisateur
     *                puisse gérer l'affichage
     */
    void pause();

    /**
     * @brief resume - libère les threads en attente sur pause
     */
    void resume();
private:
    QWaitCondition qwcond;
    QMutex mutex;
};

#endif // SYNCHROCONTROLLER_H
