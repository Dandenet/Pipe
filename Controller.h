#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>

class MainWindow;
class Model;

class Controller
{
public:
    Controller(MainWindow* pView = nullptr, Model* pModel = nullptr);
public:
    void Attach(MainWindow* pView);
    void Attach(Model* pModel);

    void ReadMessage(size_t size);
    void AddMessage(const std::string& message);

    void ForkProcess();
    void KillProcess();
    void SelectProcess(size_t index);
    void SelectDescriptor(size_t index);
private:
    MainWindow* m_pView;
    Model*      m_pModel;
};

#endif // CONTROLLER_H
