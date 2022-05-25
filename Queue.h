#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>

using byte = uint8_t;


constexpr uint64_t deffaultBufferSize = 0xFF;

class Queue
{
public:
    Queue(uint64_t maxBufferSize = deffaultBufferSize);
    ~Queue();

    Queue(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator= (const Queue&) = delete;
    Queue&& operator= (Queue&&) = delete;
public:
    void Read(byte* buffer, uint64_t bufferSize);
    void Write(const byte* buffer, uint64_t bufferSize);
    const byte* GetData() const;
    uint64_t BufferSize() const;

private:
    uint64_t    m_BufferSize;
    uint64_t    m_MaxBufferSize;

    byte*       m_pData;
};

#endif // QUEUE_H
