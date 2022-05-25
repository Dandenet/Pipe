#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    void Attach(Model* model);
    void Attach(Controller* controller);
    void ShowError(const std::string& error);

    void UpdateProcess(size_t start, size_t end);
    void DeleteProcess(size_t start, size_t end);
    void UpdateDescriptor(size_t start, size_t end);
    void DeleteDescriptor(size_t start, size_t end);
    void UpdateBuffer();
    void ShowText(const std::string& message);
private slots:
    // The parent process write button click handler
    void on_parentPrcWriteButton_clicked();

    // The fork parent process button clicked handler
    void on_forkButton_clicked();

    // The kill child process button handler
    void on_killProcessButton_clicked();

    // Index of the process changed handler
    void on_childProcessBox_currentIndexChanged(int index);

    // Index of the descriptor changed handler
    void on_fileDescriptorBox_currentIndexChanged(int index);

    void on_readButton_clicked();

private:
    Ui::MainWindow* ui;
    Model*          m_Model;
    Controller*     m_Controller;
};
#endif // MAINWINDOW_H
