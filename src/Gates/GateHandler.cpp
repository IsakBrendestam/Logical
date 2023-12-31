#include "GateHandler.h"

#include "Debug.h"

int GateHandler::m_removeGateIndex = -1;
int GateHandler::m_movingGateIndex = -1;
std::vector<Gate*> GateHandler::m_gates;
std::vector<Connection*> GateHandler::m_connections;
Connection* GateHandler::m_tempConnection = nullptr;
State GateHandler::m_state = State::DEFAULT;

void GateHandler::Initialize()
{
    m_gates.push_back(new Button(100, 600));
    m_gates.push_back(new Button(100, 500));
    m_gates.push_back(new NotGate(300, 300));
    m_gates.push_back(new AndGate(500, 500));
    m_gates.push_back(new Lamp(900, 300));
    m_gates.push_back(new OrGate(200, 800));
}

void GateHandler::Deconstruct()
{
    for (auto& gate : m_gates)
        delete gate;
    
    for (auto& connection : m_connections)
        delete connection;

    if (m_tempConnection != nullptr)
        delete m_tempConnection;
}

void GateHandler::Save()
{
    Log("Saving");

    json data;

    for (int i = 0; i  < m_gates.size(); i++)
        data["gateData"][i] = m_gates[i]->Save();

    for (int i = 0; i < m_connections.size(); i++)
        data["connectionData"][i] = m_connections[i]->Save();


    FileManager::SaveJson(data, "test.json");
}

void GateHandler::Load()
{
    Log("Loading");

    json data;
    data = FileManager::LoadJson("test.json");

    m_gates.clear();
    m_connections.clear();

    // Loading Gate
    for (auto& d : data["gateData"])
    {
        std::string type = d["type"];
        if (type == "AND")
            m_gates.push_back(new AndGate(d["xPos"], d["yPos"], d["id"]));
        else if (type == "OR")
            m_gates.push_back(new OrGate(d["xPos"], d["yPos"], d["id"]));
        else if (type == "NOT")
            m_gates.push_back(new NotGate(d["xPos"], d["yPos"], d["id"]));
        else if (type == "LAMP")
            m_gates.push_back(new Lamp(d["xPos"], d["yPos"], d["id"]));
        else if (type == "BUTTON")
            m_gates.push_back(new Button(d["xPos"], d["yPos"], d["id"]));
        else if (type == "CLOCK")
            m_gates.push_back(new Clock(d["xPos"], d["yPos"], d["interval"], d["id"]));
        else if (type == "DISPLAY")
            m_gates.push_back(new Display(d["xPos"], d["yPos"], d["id"]));
    }

    for (auto& d : data["connectionData"])
    {
        json inData = d["input"];
        json outData = d["output"];

        Gate* inputGate = GetGate(inData["gateId"]);
        Gate* outputGate = GetGate(outData["gateId"]);

        Connection* connection = new Connection(inputGate->GetInputPin(inData["pinId"]));
        connection->SetSecondPin(outputGate->GetOutputPin(outData["pinId"]));

        m_connections.push_back(connection);
    }
}

void GateHandler::Update(double deltaTime)
{
    if (!MS::lBtnDown && m_movingGateIndex != -1)
        m_movingGateIndex = -1;

    if (!MS::rBtnDown && m_removeGateIndex != -1)
        m_removeGateIndex = -1;

    // Update Gates Logic
    for (auto& gate : m_gates)
        gate->Logic(deltaTime);

    switch (m_state)
    {
    case State::DEFAULT:
        for (int i = 0; i < m_gates.size(); i++)
            CheckGateSelection(i);

        if (m_movingGateIndex >= 0)
            m_state = State::MOVING;

        CreateConnection();

        if (m_removeGateIndex >= 0)
            RemoveGate();

        break;

    case State::MOVING:
        for (int i = 0; i < m_gates.size(); i++)
            CheckGateSelection(i);

        if (m_movingGateIndex < 0)
            m_state = State::RESETTING;

        HandleGateMovement(m_movingGateIndex); 

        break;
    
    case State::CONNECTING:
        CloseConnection();

        break;
    
    case State::RESETTING:
        if (!MS::lBtnDown && !MS::rBtnDown)
            m_state = State::DEFAULT;
        break;
    }

    HandleConnections();
}

Gate* GateHandler::GetGate(int id)
{
    for (auto& gate : m_gates)
        if (gate->GetId() == id)
            return gate;
    return nullptr;
}

void GateHandler::CreateConnection()
{
    for (auto& gate : m_gates)
    {
        Pin* selectedPin = gate->GetSelectedPin();
        if (selectedPin != nullptr)
            if (!selectedPin->IsInput() || !selectedPin->GetConnected())
            {
                m_tempConnection = new Connection(selectedPin);
                m_state = State::CONNECTING;
            }
    }
}

void GateHandler::CloseConnection()
{
    m_tempConnection->Update();

    for (auto& gate : m_gates)
    {
        Pin* selectedPin = gate->GetSelectedPin();
        if (selectedPin != nullptr)
        {
            bool notSamePin = !(selectedPin->GetId() == m_tempConnection->GetFirstPin()->GetId() && 
                                selectedPin->GetGateId() == m_tempConnection->GetFirstPin()->GetGateId());
            bool notSameGate = selectedPin->GetGateId() != m_tempConnection->GetFirstPin()->GetGateId();
            bool notSameType = selectedPin->IsInput() != m_tempConnection->GetFirstPin()->IsInput();
            bool outPutNotConnected = !selectedPin->IsInput() || !selectedPin->GetConnected();

            if (notSamePin && notSameGate && notSameType && outPutNotConnected)
            {
                m_tempConnection->SetSecondPin(selectedPin);
                m_connections.push_back(m_tempConnection);
                m_tempConnection = nullptr;
                m_state = State::RESETTING;
            }
        }
    }

    if (MS::rBtnDown)
    {
        delete m_tempConnection;
        m_tempConnection = nullptr;
        m_state = State::RESETTING;
    }
}

void GateHandler::HandleConnections()
{
    for (auto& connection : m_connections)
    {
        connection->Update();
    }
}

void GateHandler::CheckGateSelection(int index)
{
    Gate* gate = m_gates[index];
    bool hover = gate->Hover(MS::x, MS::y);

    if (hover && MS::lBtnDown && m_movingGateIndex == -1)
    {
        gate->Select(MS::x, MS::y);
        m_movingGateIndex = index;
    }
    else if (hover && MS::rBtnDown && m_removeGateIndex == -1)
    {
        m_removeGateIndex = index;
    }
}

void GateHandler::HandleGateMovement(int index)
{
    if (index < 0 || index >= m_gates.size())
        return;

    Gate* gate = m_gates[index];

    gate->Move(MS::x, MS::y);
}

void GateHandler::RemoveGate()
{
    // Delete Connections
    // Check inputs
    for (auto& pin : m_gates[m_removeGateIndex]->GetInputPins())
        for (int i = m_connections.size()-1; i >= 0; i--)
            if (pin->GetId() == m_connections[i]->GetInPin()->GetId() &&
                pin->GetGateId() == m_connections[i]->GetInPin()->GetGateId())
            {
                delete m_connections[i];
                m_connections.erase(m_connections.begin() + i);
            }
    
    // Check outputs
    for (auto& pin : m_gates[m_removeGateIndex]->GetOutputPins())
        for (int i = m_connections.size()-1; i >= 0; i--)
            if (pin->GetId() == m_connections[i]->GetOutPin()->GetId() &&
                pin->GetGateId() == m_connections[i]->GetOutPin()->GetGateId())
            {
                delete m_connections[i];
                m_connections.erase(m_connections.begin() + i);
            }

    // Delete Gate
    delete m_gates[m_removeGateIndex];
    m_gates.erase(m_gates.begin() + m_removeGateIndex);
    m_state = State::RESETTING;
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


// ********** Add Functions **********


void GateHandler::AddAndGate()
{
    m_gates.push_back(new AndGate(MS::x, MS::y));
}

void GateHandler::AddOrGate()
{
    m_gates.push_back(new OrGate(MS::x, MS::y));
}

void GateHandler::AddNotGate()
{
    m_gates.push_back(new NotGate(MS::x, MS::y));
}

void GateHandler::AddButton()
{
    m_gates.push_back(new Button(MS::x, MS::y));
}

void GateHandler::AddLamp()
{
    m_gates.push_back(new Lamp(MS::x, MS::y));
}

void GateHandler::AddClock()
{
    m_gates.push_back(new Clock(MS::x, MS::y, 50));
}

void GateHandler::AddDisplay()
{
    m_gates.push_back(new Display(MS::x, MS::y));
}