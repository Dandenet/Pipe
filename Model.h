#ifndef MODEL_H
#define MODEL_H

#include <list>
#include <string>
#include <variant>


/**
 * @brief Model roles
 */
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
    /**
     * @brief Attaches view to the model
     * @param pView is the view
     */
    void Attach(MainWindow* pView);

    /**
     * @brief Does fork parent process
     */
    void ForkProcess();

    /**
     * @brief Creates anonimous pipe
     */
    void CreatePipe();

    /**
     * @brief Kill selected process
     */
    void KillProcess();

    /**
     * @brief Closes seclected file descriptor
     */
    void CloseDescriptor();
    /**
     * @brief Selects process from the process list
     * @param index
     */
    void SelectProcess(size_t index);

    /**
     * @brief Selects a file descriptor from descriptor list of the selected process
     * @param index
     */
    void SelectDescriptor(size_t index);

    /**
     * @brief Writes message to the chanel by the parent file descriptor
     * @param message is the message that should to write
     */
    void WriteMessage(const std::string& message);

    /**
     * @brief Read message to the chanel by selected descriptor
     * @param size is the bytes quantity that should read
     */
    void ReadMessage(size_t size);

    /**
     * @brief Returns quantity the elements with role
     * @param role can be ProcessRole or DescriptorRole
     * @return Returns quantity
     */
    size_t GetSize(const Role& role) const;

    /**
     * @brief GetData
     * @param index
     * @param role
     * @return Returns information of the model
     */
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
