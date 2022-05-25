#ifndef PROCESS_H
#define PROCESS_H
#include <list>

class FileDescriptor;

class Process
{
    static uint64_t ID;
public:
    Process();
    ~Process();
public:
    Process *Fork();
    void Add(FileDescriptor* descriptor);
    const std::list<FileDescriptor *>& GetDescriptorList() const;

    // Get descriptors quantity
    size_t GetSize() const;
    size_t GetID() const;

private:
    static uint64_t NextID();
private:
    uint64_t PID;
    uint64_t PPID;
    std::list<FileDescriptor*> m_DescriptorList;
};

#endif // PROCESS_H
