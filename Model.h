#ifndef MODEL_H
#define MODEL_H
#include <stdint.h>
#include <string>
#include <list>
#include <variant>

enum Role {
    DumpRole,
    ProcessRole,
    DescriptorRole
};

class MainWindow;
class Process;
class FileDescriptor;

class Model
{
public:
    Model();
    ~Model();
public:
    void Attach(MainWindow* pView);

    void ForkProcess();
    void CreatePipe();
    void WriteMessage(const std::string& message);
    void ReadMessage(size_t size);
    void KillProcess();

    void SelectProcess(size_t index);
    void SelectDescriptor(size_t index);

    // Returns process or descriptor quantity
    size_t GetSize(const Role& role) const;

    // Returns dump, process or descriptor info, by index
    std::variant<size_t, std::string> GetData(size_t index, const Role& role);
private:
    MainWindow*         m_pView;
    FileDescriptor*     m_ParentWriteDescriptor;
    Process*            m_pParentProcess;
    Process*            m_SelectedProcess;
    FileDescriptor*     m_SelectedDescriptor;
    std::list<Process*> m_ProcessList;
};

#endif // MODEL_H
