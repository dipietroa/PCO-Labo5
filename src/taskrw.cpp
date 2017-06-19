#include "taskrw.h"

TaskReader::TaskReader(AbstractReaderWriter *protocol) : _protocol(protocol){}

void TaskReader::run(){
    while(1) {
        _protocol->lockReading();
        std::cout << QThread::currentThread()->objectName().toStdString() << ": lecture" << std::endl;
        _protocol->unlockReading();
        sleep(1);
    }
}

TaskWriter::TaskWriter(AbstractReaderWriter *protocol) : _protocol(protocol){}

void TaskWriter::run(){
    while(1) {
        _protocol->lockWriting();
        std::cout << QThread::currentThread()->objectName().toStdString() << ": ecriture" << std::endl;
        _protocol->unlockWriting();
        sleep(1);
    }
}
