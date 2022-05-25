#include "Controller.h"
#include "Mainwindow.h"
#include "Model.h"
#include <iostream>

Controller::Controller(MainWindow *pView, Model *pModel) :
    m_pView(pView), m_pModel(pModel) {

    if (m_pView) {
        m_pView->Attach(this);
        m_pView->Attach(m_pModel);
    }

    if (m_pModel) {
        m_pModel->Attach(m_pView);

        m_pModel->CreatePipe();
//        m_pModel->ForkProcess();
    }


}

void Controller::Attach(MainWindow *pView) {
    m_pView = pView;
    m_pView->Attach(this);

    if (m_pModel)
        m_pModel->Attach(m_pView);
}

void Controller::Attach(Model *pModel) {
    m_pModel = pModel;
    m_pView->Attach(this);
    m_pModel->Attach(m_pView);

    if (m_pView)
        m_pView->Attach(m_pModel);
}

void Controller::ReadMessage(size_t size)
{
    m_pModel->ReadMessage(size);
}

void Controller::AddMessage(const std::string &message)
{
    m_pModel->WriteMessage(message);
}

void Controller::ForkProcess()
{
    m_pModel->ForkProcess();
}

void Controller::KillProcess()
{
    m_pModel->KillProcess();
}

void Controller::SelectProcess(size_t index)
{
    m_pModel->SelectProcess(index);
}

void Controller::SelectDescriptor(size_t index)
{
    m_pModel->SelectDescriptor(index);
}
