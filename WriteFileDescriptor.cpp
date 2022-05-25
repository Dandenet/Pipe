#include "WriteFileDescriptor.h"
#include "Queue.h"
#include <stdexcept>

WriteFileDescriptor::WriteFileDescriptor()
{

}

WriteFileDescriptor::WriteFileDescriptor(std::shared_ptr<Queue> &pBuffer) :
    FileDescriptor(pBuffer) {}

void WriteFileDescriptor::Read(uint8_t*, uint64_t)
{
    throw std::runtime_error("File descriptor is open to write only!");
}

void WriteFileDescriptor::Write(const uint8_t *buffer, uint64_t bufferSize)
{
    if (m_pBuffer) {
        m_pBuffer->Write(buffer, bufferSize);
    } else {
        throw std::runtime_error("File descriptor is already closed!");
    }
}

FileDescriptor *WriteFileDescriptor::Dup()
{
    return new WriteFileDescriptor(m_pBuffer);
}
