#include "Clock.h"

#include "Debug.h"

Clock::Clock(int xPos, int yPos, int interval): 
    Gate(xPos, yPos, 0, 1) 
{
    m_btnX = m_rect.x + m_rect.w/2;
    m_btnY = m_rect.y + m_rect.h/2;
    m_btnR = m_rect.h/2*0.7f;

    m_state = false;
    m_timeSinceChange = 0;

    m_interval = (double)interval/1000;
}

void Clock::Logic(double deltaTime)
{
    m_timeSinceChange += deltaTime;

    if (m_timeSinceChange >= m_interval)
    {
        m_timeSinceChange = 0;
        m_state = !m_state;
        m_outputs[0]->SetState(m_state);
    }
}

void Clock::Draw(SDL_Renderer* renderer)
{
    Gate::Draw(renderer);
    
    m_btnX = m_rect.x + m_rect.w/2;
    m_btnY = m_rect.y + m_rect.h/2;

    if (m_state)
        filledCircleColor(renderer, m_btnX, m_btnY, m_btnR, 0xff00ff00); 
    else
        filledCircleColor(renderer, m_btnX, m_btnY, m_btnR, 0xff000000);
}
