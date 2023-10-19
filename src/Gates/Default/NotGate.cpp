#include "NotGate.h"

NotGate::NotGate(int xPos, int yPos): 
    Gate(xPos, yPos, 1, 1) 
{
    m_color = { 92, 118, 105, 0 };
}

void NotGate::Logic(double deltaTime)
{
    if (m_inputs[0]->GetConnected() && m_outputs[0]->GetConnected())
        m_outputs[0]->SetState(!m_inputs[0]->GetState());
}
