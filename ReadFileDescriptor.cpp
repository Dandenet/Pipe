#include "ReadFileDescriptor.h"
#include "Queue.h"
#include <stdexcept>
ReadFileDescriptor::ReadFileDescriptor()
{

}

ReadFileDescriptor::ReadFileDescriptor(std::shared_ptr<Queue> &pBuffer)
    : FileDescriptor(pBuffer) {}

void ReadFileDescriptor::Read(uint8_t *buffer, uint64_t bufferSize)
{

    if (m_pBuffer) {
        m_pBuffer->Read(buffer, bufferSize);
    } else {
        throw std::runtime_error("File descriptor is already closed!");
    }
}

void ReadFileDescriptor::Write(const uint8_t*, uint64_t)
{
    throw std::runtime_error("File descriptor is open to read only!");
}

FileDescriptor *ReadFileDescriptor::Dup()
{
    return new ReadFileDescriptor(m_pBuffer);
}
