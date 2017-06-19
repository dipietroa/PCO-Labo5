
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
    AbstractReaderWriter* resourceManager = new ReaderWriterEqualPrioHoare();

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

        // If key is <enter>
        SynchroController::getInstance()->resume();

        // If key was <esc>
        continuing = true;
    }

    // Kill the threads

    return 0;



    // Pour ceux qui voudraient développer une version graphique
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
