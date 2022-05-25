#include "Pipe.h"
#include "Queue.h"
#include "ReadFileDescriptor.h"
#include "WriteFileDescriptor.h"

Pipe::Pipe()
{

}

std::pair<FileDescriptor *, FileDescriptor *> Pipe::Create()
{
    std::shared_ptr<Queue> pBuffer(new Queue);
    return std::make_pair<FileDescriptor*, FileDescriptor*>(
                new ReadFileDescriptor(pBuffer), new WriteFileDescriptor(pBuffer));
}
