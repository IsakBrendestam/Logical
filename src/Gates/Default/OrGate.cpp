#include "OrGate.h"

OrGate::OrGate(int xPos, int yPos): 
    Gate(xPos, yPos, 2, 1) 
{
    m_color = { 132, 158, 145, 0 };
}

void OrGate::Logic(double deltaTime)
{
    m_outputs[0]->SetState(m_inputs[0]->GetState() || m_inputs[1]->GetState());
}