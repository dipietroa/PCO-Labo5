#include "taskrw.h"

static int test = 0;

TaskReader::TaskReader(AbstractReaderWriter *protocol) : _protocol(protocol){}

void TaskReader::run(){
    while(1) {
        _protocol->lockReading();
        _protocol->unlockReading();
        sleep(1);
    }
}

TaskWriter::TaskWriter(AbstractReaderWriter *protocol) : _protocol(protocol){}

void TaskWriter::run(){
    while(1) {
        _protocol->lockWriting();
        _protocol->unlockWriting();
        sleep(1);
    }
}
