#include "Button.h"

#include "Debug.h"

Button::Button(int xPos, int yPos): 
    Gate(xPos, yPos, 0, 1) 
{
    m_color = { 92, 118, 105, 0 };
    m_btnX = m_rect.x + m_rect.w/2;
    m_btnY = m_rect.y + m_rect.h/2;
    m_btnR = m_rect.h/2*0.7f;
}

void Button::Logic(double deltaTime)
{
    m_hoverBtn = false;

    if (MyMath::Pow((MS::x-m_btnX)) + MyMath::Pow((MS::y-m_btnY)) < MyMath::Pow(m_btnR))
        m_hoverBtn = true;

    if (m_hoverBtn && MS::lBtnDown && !m_click)
    {
        // Action when button is clicked
        m_outputs[0]->SetState(!m_outputs[0]->GetState());
        m_click = true;
    }
    
    if (!m_hoverBtn || !MS::lBtnDown)
        m_click = false;
}

void Button::Draw(SDL_Renderer* renderer)
{
    Gate::Draw(renderer);

    m_btnX = m_rect.x + m_rect.h/2;
    m_btnY = m_rect.y + m_rect.h/2;
    
    if (m_click)
        filledCircleColor(renderer, m_btnX, m_btnY, m_btnR, 0xffffffff); 
    else if (m_hoverBtn)
        filledCircleColor(renderer, m_btnX, m_btnY, m_btnR, 0xff888888);
    else
        filledCircleColor(renderer, m_btnX, m_btnY, m_btnR, 0xff000000);
}
