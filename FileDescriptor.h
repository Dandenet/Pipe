#ifndef FILEDESCRIPTOR_H
#define FILEDESCRIPTOR_H
#include <stdint.h>
#include <memory>

class Queue;

class FileDescriptor
{
public:
    FileDescriptor();
    FileDescriptor(std::shared_ptr<Queue>& pBuffer);
    virtual ~FileDescriptor() = default;
public:
    virtual void Read(uint8_t* pBuffer, uint64_t bufferSize) = 0;
    virtual void Write(const uint8_t* pBuffer, uint64_t bufferSize) = 0;
    virtual FileDescriptor* Dup() = 0;

    void Close();
    const std::shared_ptr<Queue> &GetBuffer() const;

protected:
    std::shared_ptr<Queue> m_pBuffer;

};

#endif // FILEDESCRIPTOR_H
