#ifndef TASKRW_H
#define TASKRW_H

#include <iostream>
#include <QThread>
#include "abstractreaderwriter.h"
#include "waitinglogger.h"

class TaskReader :public QThread{
private:
    AbstractReaderWriter* _protocol;
public:
    void run();
    TaskReader(AbstractReaderWriter* protocol);
};

class TaskWriter :public QThread{
private:
    AbstractReaderWriter* _protocol;
public:
    void run();
    TaskWriter(AbstractReaderWriter* protocol);
};

#endif // TASKRW_H
