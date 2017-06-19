#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

#endif // ABSTRACTREADERWRITER_H
class AbstractReaderWriter {
public:
    AbstractReaderWriter();
    virtual ~AbstractReaderWriter();
    virtual void lockReading() = 0;
    virtual void lockWriting() = 0;
    virtual void unlockReading() = 0;
    virtual void unlockWriting() = 0;
};
