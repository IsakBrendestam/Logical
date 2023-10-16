#include "Lamp.h"

Lamp::Lamp(int xPos, int yPos): 
    Gate(xPos, yPos, 1, 0) 
{
    m_color = { 92, 118, 105, 0 };
    m_lampX = m_rect.x + m_rect.h/2;
    m_lampY = m_rect.y + m_rect.h/2;
    m_lampR = m_rect.h/2*0.7f;
}

void Lamp::Logic(MouseState ms)
{
    m_state = false;
    if (m_inputs[0]->GetConnected())
        m_state = m_inputs[0]->GetState();
}

void Lamp::Draw(SDL_Renderer* renderer)
{
    Gate::Draw(renderer);

    m_lampX = m_rect.x + m_rect.w/2;
    m_lampY = m_rect.y + m_rect.h/2;
    
    if (m_state)
        filledCircleColor(renderer, m_lampX, m_lampY, m_lampR, 0xff00ff00);
    else
        filledCircleColor(renderer, m_lampX, m_lampY, m_lampR, 0xff000000);
}