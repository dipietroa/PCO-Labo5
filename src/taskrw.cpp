#include "taskrw.h"

TaskReader::TaskReader(AbstractReaderWriter *protocol) : _protocol(protocol){}

void TaskReader::run(){
    while(1) {
        _protocol->lockReading();
        ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
        _protocol->unlockReading();
        ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
        sleep(1);
    }
}

TaskWriter::TaskWriter(AbstractReaderWriter *protocol) : _protocol(protocol){}

void TaskWriter::run(){
    while(1) {
        _protocol->lockWriting();
        ((ReadWriteLogger*)WaitingLogger::getInstance())->addResourceAccess(QThread::currentThread()->objectName());
        _protocol->unlockWriting();
        ((ReadWriteLogger*)WaitingLogger::getInstance())->removeResourceAccess(QThread::currentThread()->objectName());
        sleep(1);
    }
}
