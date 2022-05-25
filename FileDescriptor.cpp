#include "FileDescriptor.h"

FileDescriptor::FileDescriptor() :
    m_pBuffer(nullptr) {}

FileDescriptor::FileDescriptor(std::shared_ptr<Queue> &pBuffer) :
    m_pBuffer(pBuffer) {}

void FileDescriptor::Close()
{
    m_pBuffer = nullptr;
}

const std::shared_ptr<Queue> &FileDescriptor::GetBuffer() const
{
    return m_pBuffer;
}
