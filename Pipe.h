#ifndef PIPE_H
#define PIPE_H
#include <list>


class FileDescriptor;

class Pipe
{
public:
    Pipe();
public:
    static std::pair<FileDescriptor*, FileDescriptor*> Create();
};

#endif // PIPE_H
