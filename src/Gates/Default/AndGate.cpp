#include "AndGate.h"

AndGate::AndGate(int xPos, int yPos): 
    Gate(xPos, yPos, 2, 1) 
{
    m_color = { 92, 118, 105, 0 };
}

void AndGate::Logic(MouseState ms)
{
    m_outputs[0]->SetState(m_inputs[0]->GetState() && m_inputs[1]->GetState());
}