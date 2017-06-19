/**
  * DOCUMENTATION
  *********************************************
  * Les premières méthodes que nous avons implémentées dans le programme
  * sont celles nous permettant de gérer les logs. Nous avons complété les
  * classes WaitingQueue, WaitingLogger et ReadWriteLogger selon les prototypes
  * de méthodes fournies. Ces classes proposent simplement la visualisation des
  * files d'attentes sur un objet de synchronisation ex: (lecteur 1 attend sur semaphore1)
  *
  * Une fois toutes les méthodes nécessaires à la manipulation de ces files d'attentes implémentées
  * nous avons créé nos "wrapper" des objets de synchronisation proposés par Qt. Nous les appelons
  * wrapper car nous utilisons dans ces classes les objets correspondant soit un QMutex pour OMutex
  * un QSemaphore pour OSemaphore etc. Il n'y a que le moniteur de hoare qui est vraiment implémenté
  * car Qt ne propose pas sa classe. Ces objets sont donc enveloppés pour que nous puissions manipuler
  * progressivement nos files d'attente. Par exemple, pour la classe OMutex, lors d'un lock() nous ajoutons
  * le thread ayant fait appel à cette méthode dans la liste d'attente liée au OMutex instancié. Encore
  * dans cette même méthode, à la toute fin, nous supprimons le thread de la liste, car lorsqu'il atteind
  * la fin de la méthode, c'est que la section critique a été libérée et qu'il n'est donc plus en attente
  * sur l'objet de synchronisation.
  *
  * Nous avons utilisé cette façon de gérér les listes d'attente sur tous nos objets de synchronisation.
  * Nous sommes certains de l'implémentation pour les OSemaphore ainsi que les OMutex mais moins pour
  * OWaitCondition et OHoareMonitor, étant donné que nous avons eu beaucoup d'effets de bord durant le laboratoire.
  *
  * Nous avons ensuite créé les protocoles lecteurs/rédacteurs. Nous avons une classe abstraite
  * étant le modèle sur lequel se calquent les protocoles puis nos 6 protocoles concrets. Dans ces 6 protocoles
  * nous en avons deux qui gèrent différement la priorité entre lecteurs rédacteurs et pour chacun d'eux les trois
  * gestion avec les différents objets de synchro. Nous avons implémenté les protocoles priorité aux lecteurs
  * ainsi que priorité égale.
  *
  * Pour changer de protocole, il faut modifier la première ligne dans la méthode main en passant une autre instance
  * d'un protocole concret parmis ceux implémentés.
  *
  * Nous avons implémenté la plus part de ces protocoles en nous inspirant de solutions d'exercices, sauf pour la priorité
  * aux lecteurs avec moniteur de mesa et moniteur de Hoare.
  *
  * Les problèmes que nous avons rencontrés et qui subsistent encore sont nombreux. Nous ne savons pas si ils viennent
  * de la façon dont nous affichons les informations ou des protocoles eux-mêmes. Nous avons eu beaucoup de difficultés
  * à débuger l'application et à trouver les erreurs.
  */
#include <QApplication>

#define NB_WRITERS 1
#define NB_READERS 3
#define ENTER 10
#define ESC 27

#include "synchrocontroller.h"
#include "taskrw.h"
#include "abstractreaderwriter.h"
#include "readerwriterprioreaderssem.h"
#include "readerwriterequalpriosem.h"
#include "readerwriterequalpriomesa.h"
#include "readerwriterequalpriohoare.h"

int main(int argc, char *argv[])
{

    // Create the resource manager object

    //INFO : Il suffit de changer l'instance concrète readerwriter en choisissant
    //parmis celles implémentées pour tester un autre protocole lecteur
    //rédacteur avec une gestion différente des priorités ou un autre type
    //d'objets de synchronisation
    AbstractReaderWriter* resourceManager = new ReaderWriterPrioReadersSem();

    // Create the threads
    TaskWriter* threadsWriter[NB_WRITERS];
    TaskReader* threadsReader[NB_READERS];


    for(int i = 0; i < NB_READERS; i++){
        threadsReader[i] = new TaskReader(resourceManager);
        threadsReader[i]->setObjectName(QString::fromStdString("R" +  std::to_string(i)));
    }

    for(int i = 0; i < NB_WRITERS; i++){
        threadsWriter[i] = new TaskWriter(resourceManager);
        threadsWriter[i]->setObjectName(QString::fromStdString("W" +  std::to_string(i)));
    }

    // Start the threads
    for(int i = 0; i < NB_READERS; i++)
        threadsReader[i]->start();

    for(int i = 0; i < NB_WRITERS; i++)
        threadsWriter[i]->start();

    bool continuing = true;
    char key;

    while (continuing) {
        // Wait for a key press
        std::cin.get(key);
        switch (key) {
            case ENTER:
                SynchroController::getInstance()->resume();
                break;
            case ESC:
                continuing = false;
                break;
        }

    }

    // Kill the threads
    for(int i = 0; i < NB_READERS; i++) {
        threadsReader[i]->terminate();
    }

    for(int i = 0; i < NB_WRITERS; i++) {
        threadsWriter[i]->terminate();
    }

    return EXIT_SUCCESS;
}
