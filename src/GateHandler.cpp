#include "GateHandler.h"
#include "Debug.h"

int GateHandler::m_movingGateIndex;
std::vector<Gate*> GateHandler::m_gates;
std::vector<Connection*> GateHandler::m_connections;
Connection* GateHandler::m_tempConnection = nullptr;
State GateHandler::m_state = State::DEFAULT;

void GateHandler::AddAndGate()
{
    m_gates.push_back(new AndGate(MS::x, MS::y));
}

void GateHandler::Initialize()
{
    m_gates.push_back(new Button(100, 600));
    m_gates.push_back(new Button(100, 500));
    m_gates.push_back(new NotGate(300, 300));
    m_gates.push_back(new AndGate(500, 500));
    m_gates.push_back(new Lamp(900, 300));
}

void GateHandler::Update(double deltaTime, MouseState ms)
{
    // Update Gates Logic
    for (auto& gate : m_gates)
        gate->Logic(ms);

    switch (m_state)
    {
    case State::DEFAULT:
        for (int i = 0; i < m_gates.size(); i++)
            CheckGateSelection(ms, i);

        if (m_movingGateIndex >= 0)
            m_state = State::MOVING;

        CreateConnection(ms);

        break;

    case State::MOVING:
        for (int i = 0; i < m_gates.size(); i++)
            CheckGateSelection(ms, i);

        if (m_movingGateIndex < 0)
            m_state = State::RESETTING;

        HandleGateMovement(ms, m_movingGateIndex); 

        break;
    
    case State::CONNECTING:
        CloseConnection(ms);

        break;
    
    case State::RESETTING:
        if (!ms.lBtnDown)
            m_state = State::DEFAULT;
        break;
    }

    HandleConnections(ms);
}

void GateHandler::CreateConnection(MouseState ms)
{
    for (auto& gate : m_gates)
    {
        Pin* selectedPin = gate->GetSelectedPin(ms);
        if (selectedPin != nullptr)
            if (!selectedPin->IsInput() || !selectedPin->GetConnected())
            {
                m_tempConnection = new Connection(selectedPin);
                m_state = State::CONNECTING;
            }
    }
}

void GateHandler::CloseConnection(MouseState ms)
{
    m_tempConnection->Update(ms);

    for (auto& gate : m_gates)
    {
        Pin* selectedPin = gate->GetSelectedPin(ms);
        if (selectedPin != nullptr)
        {
            if (selectedPin->GetId() != m_tempConnection->GetPin1()->GetId() &&
                selectedPin->IsInput() != m_tempConnection->GetPin1()->IsInput() &&
                !selectedPin->GetConnected())
            {
                m_tempConnection->SetPin2(selectedPin);
                m_connections.push_back(m_tempConnection);
                m_tempConnection = nullptr;
                m_state = State::RESETTING;
            }
        }
    }
}

void GateHandler::HandleConnections(MouseState ms)
{
    for (auto& connection : m_connections)
    {
        connection->Update(ms);
    }
}

void GateHandler::CheckGateSelection(MouseState ms, int index)
{
    Gate* gate = m_gates[index];
    bool hover = gate->Hover(ms.x, ms.y);

    if (hover && ms.lBtnDown && m_movingGateIndex == -1)
    {
        gate->Select(ms.x, ms.y);
        m_movingGateIndex = index;
    }

    if (!ms.lBtnDown)
        m_movingGateIndex = -1;
}

void GateHandler::HandleGateMovement(MouseState ms, int index)
{
    if (index < 0 || index >= m_gates.size())
        return;

    Gate* gate = m_gates[index];

    gate->Move(ms.x, ms.y);
}

void GateHandler::Draw(SDL_Renderer* renderer)
{
    for (int i = 0; i < m_gates.size(); i++)
        if (i != m_movingGateIndex)
            m_gates[i]->Draw(renderer);

    if (m_movingGateIndex >= 0)
        m_gates[m_movingGateIndex]->Draw(renderer);

    if (m_tempConnection != nullptr)
        m_tempConnection->Draw(renderer);

    for (auto& connection : m_connections)
        connection->Draw(renderer);
}