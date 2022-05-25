#include "Process.h"
#include "FileDescriptor.h"

uint64_t Process::ID = 2222;

Process::Process() : PID(NextID()), PPID(0)
{}

Process::~Process()
{
    for (auto& descriptor : m_DescriptorList) {
        if (descriptor) {
            delete descriptor;
        }
    }
}

Process *Process::Fork()
{
    Process* process = new Process;

    for (auto& descriptor : m_DescriptorList) {
        process->m_DescriptorList.push_back(descriptor->Dup());
    }

    process->PPID = PID;

    return process;
}

void Process::Add(FileDescriptor *descriptor)
{
    m_DescriptorList.push_back(descriptor);
}

uint64_t Process::NextID()
{
    return ID++;
}

const std::list<FileDescriptor *> &Process::GetDescriptorList() const
{
    return m_DescriptorList;
}

size_t Process::GetSize() const
{
    return m_DescriptorList.size();
}

size_t Process::GetID() const
{
    return PID;
}
