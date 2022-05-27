#include "Model.h"
#include "Pipe.h"
#include "Process.h"
#include "FileDescriptor.h"
#include "Mainwindow.h"
#include "Queue.h"
#include <sstream>
#include <exception>
#include <iostream>


//------------------------------------------------------------------------------------------
Model::Model() :
    m_pParentProcess(new Process),
    m_SelectedProcess(nullptr),
    m_SelectedDescriptor(nullptr) {}

//------------------------------------------------------------------------------------------
Model::~Model()
{
    if (m_pParentProcess)
        delete  m_pParentProcess;

    for (auto& process : m_ProcessList)
        delete process;
}

//------------------------------------------------------------------------------------------
void Model::Attach(MainWindow *pView)
{
    m_pView = pView;
}

//------------------------------------------------------------------------------------------
void Model::CreatePipe()
{
    auto descriptor = Pipe::Create();
    m_pParentProcess->Add(descriptor.first);
    m_pParentProcess->Add(descriptor.second);

    m_ParentWriteDescriptor = descriptor.second;
    m_pView->UpdateBuffer();
}

//------------------------------------------------------------------------------------------
void Model::ForkProcess()
{
    auto pChildProcess = m_pParentProcess->Fork();
    m_ProcessList.push_back(pChildProcess);

    size_t index = m_ProcessList.size();
    m_pView->UpdateProcess(0, index);
}

//------------------------------------------------------------------------------------------
void Model::WriteMessage(const std::string &message)
{
    try {
        m_ParentWriteDescriptor->Write((uint8_t*)message.c_str(), message.size() * sizeof (char));
        m_pView->UpdateBuffer();
    } catch(const std::exception& e) {
        m_pView->ShowError(e.what());
    }
}


//------------------------------------------------------------------------------------------
void Model::ReadMessage(size_t size)
{
    try {
        if (!m_SelectedDescriptor)
            throw std::exception("Descriptor doesn't selected");

        std::string buffer(1024, '\0');
        m_SelectedDescriptor->Read((uint8_t*)&buffer[0], size);
        m_pView->ShowText(buffer);
        m_pView->UpdateBuffer();

    } catch(const std::exception& e) {

        m_pView->ShowError(e.what());
    }

}

//------------------------------------------------------------------------------------------
void Model::KillProcess()
{
    // Clear descriptor list
    if (m_SelectedProcess) {
        auto size = m_SelectedProcess->GetDescriptorList().size();
        m_pView->DeleteDescriptor(0, size);
    }

    // Find index to update
    size_t index = 0;
    auto it = m_ProcessList.begin();
    while (it != m_ProcessList.end()  && *it != m_SelectedProcess) {
        ++index;
        ++it;
    };

    // Delete process from list
    m_ProcessList.remove(m_SelectedProcess);
    delete m_SelectedProcess;
    m_SelectedProcess = nullptr;
    m_SelectedDescriptor = nullptr;

    m_pView->DeleteProcess(index, index + 1);
}

//------------------------------------------------------------------------------------------
void Model::CloseDescriptor()
{
    if (!m_SelectedDescriptor)
        return;

    auto& list = m_SelectedProcess->GetDescriptorList();
    size_t index = 0;

    // find index of the descriptor should to delete
    auto it = list.begin();
    for (; it != list.end() && *it != m_SelectedDescriptor; ++it) {
        ++index;
    }

    assert((it != list.end()));

    m_SelectedDescriptor->Close();
    list.remove(m_SelectedDescriptor);
    delete m_SelectedDescriptor;
    m_SelectedDescriptor = nullptr;

    m_pView->DeleteDescriptor(index, index + 1);
}

//------------------------------------------------------------------------------------------
void Model::SelectProcess(size_t index)
{
    if (index > m_ProcessList.size())
        return;

    // Clear descriptor list for selected process
    if (m_SelectedProcess) {
        size_t size = m_SelectedProcess->GetDescriptorList().size();
        m_pView->DeleteDescriptor(0, size);
    }

    // Select process
    m_SelectedProcess = *std::next(m_ProcessList.begin(), index);


    // Update descriptors for selected process
    size_t quantity = m_SelectedProcess->GetSize();
    m_pView->UpdateDescriptor(0, quantity);
}

//------------------------------------------------------------------------------------------
void Model::SelectDescriptor(size_t index)
{
    if (m_SelectedProcess && m_SelectedProcess->GetSize() > index) {
        auto it = m_SelectedProcess->GetDescriptorList().begin();
        m_SelectedDescriptor = *std::next(it, index);
    }
}

//------------------------------------------------------------------------------------------
size_t Model::GetSize(const Role& role) const
{
    if (role == ProcessRole) {
        return m_ProcessList.size();
    } else if (role == DescriptorRole) {
        return m_SelectedProcess->GetSize();
    }

    // Undefined role
    return 0;
}

//------------------------------------------------------------------------------------------
std::variant<size_t, std::string> Model::GetData(size_t index, const Role& role)
{
    if (role == ProcessRole && index < m_ProcessList.size()) {

        // Returns child process ID
        auto it = std::next(m_ProcessList.begin(), index);
        return (*it)->GetID();

    } else if (role == DescriptorRole
               && m_SelectedProcess != nullptr
               && index < m_SelectedProcess->GetSize()) {

        // Return child process descrtiptor information
        return index;

    } else if (role == DumpRole) {

            auto buffer = m_ParentWriteDescriptor->GetBuffer();
            std::stringstream ss;

            auto* bufferWalker = buffer->GetData();
            for (size_t i = 0; i < buffer->BufferSize(); ++i) {
                ss << std::hex << static_cast<short>(*bufferWalker);
                ++bufferWalker;

                if (i % 2)
                    ss << " ";
            }

        // Returns dump buffer
        return std::string(ss.str());
    }

    // undefined role
    return {};
}
