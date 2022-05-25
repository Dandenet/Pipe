#ifndef READFILEDESCRIPTOR_H
#define READFILEDESCRIPTOR_H
#include "FileDescriptor.h"


class ReadFileDescriptor : public FileDescriptor
{
public:
    ReadFileDescriptor();
    ReadFileDescriptor(std::shared_ptr<Queue>& pBuffer);
public:
    void Read(uint8_t* buffer, uint64_t bufferSize) override;
    void Write(const uint8_t* buffer, uint64_t bufferSize) override;
    FileDescriptor* Dup() override;

};

#endif // READFILEDESCRIPTOR_H
