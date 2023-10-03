#include "GateHandler.h"
#include <iostream>

int GateHandler::m_movingGateIndex;
std::vector<Gate*> GateHandler::m_gates;

void GateHandler::Initialize()
{
    m_gates.push_back(new Gate(300, 300, 1, 1));
    m_gates.push_back(new AndGate(500, 500));
}

void GateHandler::Update(double deltaTime, MouseState ms)
{
    for (int i = 0; i < m_gates.size(); i++)
    {
        CheckGateSelection(ms, i);
        m_gates[i]->Logic();
    }

    if (m_movingGateIndex >= 0)
        HandleGateMovement(ms, m_movingGateIndex);
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
}