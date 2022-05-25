#ifndef WRITEFILEDESCRIPTOR_H
#define WRITEFILEDESCRIPTOR_H

#include "FileDescriptor.h"

class WriteFileDescriptor : public FileDescriptor
{
public:
    WriteFileDescriptor();
    WriteFileDescriptor(std::shared_ptr<Queue>& pBuffer);
public:
    void Read(uint8_t* buffer, uint64_t bufferSize) override;
    void Write(const uint8_t* buffer, uint64_t bufferSize) override;
    FileDescriptor* Dup() override;

};

#endif // WRITEFILEDESCRIPTOR_H
