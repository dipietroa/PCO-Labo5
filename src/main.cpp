
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

    //Il suffit de changer l'instance concrète readerwriter en choisissant
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

    while (continuing) {
        // Wait for a key press
        char key;
        forever {
            std::cin.get(key);
            switch (key) {
            case ENTER:
                SynchroController::getInstance()->resume();
                break;
            case ESC:
                return EXIT_SUCCESS;
                break;
            }
        }
    }

    // Kill the threads
    for(int i = 0; i < NB_READERS; i++) {
        threadsReader[i]->wait();
    }

    for(int i = 0; i < NB_WRITERS; i++) {
        threadsWriter[i]->wait();
    }

    return 0;
}
