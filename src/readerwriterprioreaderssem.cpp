#include "readerwriterprioreaderssem.h"

ReaderWriterPrioReadersSem::ReaderWriterPrioReadersSem() : mutexReaders(1),
                                                     mutexWriters(1),
                                                     writer(1),
                                                     nbReaders(0){}
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
