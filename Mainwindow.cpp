#include "Mainwindow.h"
#include "./ui_Mainwindow.h"
#include <QMessageBox>
#include "Controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Attach(Model* model)
{
    m_Model = model;
}

void MainWindow::Attach(Controller* controller)
{
    m_Controller = controller;
}

void MainWindow::ShowError(const std::string &error)
{
    QMessageBox msg;
    msg.setText(QString::fromStdString(error));
    msg.show();
    msg.exec();
}

#include <iostream>

//------------------------------------------------------------------------------------------
void MainWindow::UpdateProcess(size_t start, size_t end)
{
    for (size_t index = start; index < end; ++index) {
        auto data = m_Model->GetData(index, ProcessRole);
        size_t pid = std::get<size_t>(data);
        auto text = QString("Proces ID: %1").arg(pid);

        if (ui->childProcessBox->count() <= index) {
            try {
                ui->childProcessBox->addItem(text);

            } catch(std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        } else {
            ui->childProcessBox->setItemText(static_cast<int>(index), text);
        }
    }
}

//------------------------------------------------------------------------------------------
void MainWindow::DeleteProcess(size_t start, size_t end)
{
    for (size_t index = start; index < end; --end) {
        ui->childProcessBox->removeItem(static_cast<int>(index));
    }
}

//------------------------------------------------------------------------------------------
void MainWindow::UpdateDescriptor(size_t start, size_t end)
{
    for (size_t index = start; index < end; ++index) {
        auto data = m_Model->GetData(index, DescriptorRole);
        size_t id = std::get<size_t>(data);
        auto text = QString("File descriptor %1").arg(id);

        if (ui->fileDescriptorBox->count() <= index) {
            ui->fileDescriptorBox->addItem(text);
        } else {
            ui->fileDescriptorBox->setItemText(static_cast<int>(index), text);
        }
    }
}

//------------------------------------------------------------------------------------------
void MainWindow::DeleteDescriptor(size_t start, size_t end)
{
    for (size_t index = start; index < end; --end) {
        ui->fileDescriptorBox->removeItem(static_cast<int>(index));
    }
}

//------------------------------------------------------------------------------------------
void MainWindow::UpdateBuffer()
{
    auto buffer = std::get<std::string>(m_Model->GetData(0, DumpRole));
    ui->dumpBuffer->setText(QString::fromStdString(buffer).toUpper());
}


//------------------------------------------------------------------------------------------
void MainWindow::ShowText(const std::string &message)
{
    ui->childPrcLineEdit->setText(message.c_str());
}


//------------------------------------------------------------------------------------------
void MainWindow::on_parentPrcWriteButton_clicked()
{
    auto text = ui->parentPrcLineEdit->text();

    if(!text.isEmpty()) {
        m_Controller->AddMessage(text.toStdString());
    }
}


//------------------------------------------------------------------------------------------
void MainWindow::on_forkButton_clicked()
{
    m_Controller->ForkProcess();
}

//------------------------------------------------------------------------------------------
void MainWindow::on_childProcessBox_currentIndexChanged(int index)
{
    if (m_Model->GetSize(ProcessRole) >= index) {
        m_Controller->SelectProcess(static_cast<size_t>(index));
        ui->fileDescriptorBox->setCurrentIndex(0);
    }
}


//------------------------------------------------------------------------------------------
void MainWindow::on_killProcessButton_clicked()
{
    m_Controller->KillProcess();
}

//------------------------------------------------------------------------------------------
void MainWindow::on_fileDescriptorBox_currentIndexChanged(int index)
{
    m_Controller->SelectDescriptor(index);
}

//------------------------------------------------------------------------------------------
void MainWindow::on_readButton_clicked()
{
    size_t size = ui->bytesSpinBox->value();
    if (size > 0) {
        m_Controller->ReadMessage(size);
    }
}

