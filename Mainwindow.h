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


    /**
     * @brief Shows error message box
     * @param error is the error text
     */
    void ShowError(const std::string& error);

    /**
     * @brief Updates child process combo box in the cycle
     * if the qualtity of the elements less then index
     * it inserts a new element in the box, else it updates
     * @param start is the start index to update
     * @param end is the end index to update
     */
    void UpdateProcess(size_t start, size_t end);


    /**
     * @brief Delete elements from child process combo box in the cycle
     * @param start is the start index to delete
     * @param is the end index to delete
     */
    void DeleteProcess(size_t start, size_t end);

    /**
     * @brief Updates file descriptor combo box in the cycle
     * if the qualtity of the elements less then index
     * it inserts a new element in the box, else it updates
     * @param start is the start index to update
     * @param end is the end index to update
     */
    void UpdateDescriptor(size_t start, size_t end);


    /**
     * @brief Delete elements from file descriptor combo box in the cycle
     * @param start is the start index to delete
     * @param is the end index to delete
     */
    void DeleteDescriptor(size_t start, size_t end);

    /**
     * @brief Update content of the dump buffer
     */
    void UpdateBuffer();

    /**
     * @brief Shows the message read by file descriptor
     * @param message is data read from the chanel
     */
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

    void on_createPipe_clicked();

    void on_closeButton_clicked();

private:
    Ui::MainWindow* ui;
    Model*          m_Model;
    Controller*     m_Controller;
};
#endif // MAINWINDOW_H
