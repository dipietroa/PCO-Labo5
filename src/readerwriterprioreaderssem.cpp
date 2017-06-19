#include "readerwriterprioreaderssem.h"

ReaderWriterPrioReadersSem::ReaderWriterPrioReadersSem() : mutexReaders(1, QString::fromStdString("mutexReaders")),
                                                     mutexWriters(1, QString::fromStdString("mutexWriters")),
                                                     writer(1, QString::fromStdString("writer")),
                                                     nbReaders(0){}

ReaderWriterPrioReadersSem::~ReaderWriterPrioReadersSem(){

}

void ReaderWriterPrioReadersSem::lockReading(){
    mutexReaders.acquire();
    nbReaders++;

    if (nbReaders==1)
        writer.acquire();

    mutexReaders.release();
}

void ReaderWriterPrioReadersSem::lockWriting(){
    mutexWriters.acquire();
    writer.acquire();
}

void ReaderWriterPrioReadersSem::unlockReading(){
    mutexReaders.acquire();
    nbReaders -= 1;

    if (nbReaders==0)
        writer.release();

    mutexReaders.release();
}

void ReaderWriterPrioReadersSem::unlockWriting(){
    writer.release();
    mutexWriters.release();
}
