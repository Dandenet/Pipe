#include "Queue.h"
#include <memory.h>
#include <stdexcept>

Queue::Queue(uint64_t maxBufferSize) :
    m_BufferSize( 0 ),
    m_MaxBufferSize( maxBufferSize ),
    m_pData ( new byte [m_MaxBufferSize] )
{
    memset(m_pData, 0xFF, m_MaxBufferSize * sizeof (byte));
}

void Queue::Read(byte* pBuffer, uint64_t bufferSize)
{
    if (bufferSize > m_BufferSize)
        throw std::runtime_error("Buffer doesn't contain so much bytes!");

    memcpy(pBuffer, m_pData, bufferSize);

    // shift bytes to left
    m_BufferSize -= bufferSize;
    memcpy(m_pData, m_pData + bufferSize, m_BufferSize);
}

void Queue::Write(const byte* pBuffer, uint64_t bufferSize)
{
    if (m_MaxBufferSize < bufferSize + m_BufferSize)
        throw std::runtime_error("Buffer full!");

    memcpy(m_pData + m_BufferSize, pBuffer, bufferSize);
    m_BufferSize += bufferSize;
}

const byte *Queue::GetData() const
{
    return m_pData;
}

uint64_t Queue::BufferSize() const
{
    return m_MaxBufferSize;
}

Queue::~Queue()
{
    if (m_pData)
        delete [] m_pData;
}


