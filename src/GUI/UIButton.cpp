#include "UIButton.h"

UIButton::UIButton(int x, int y, int w, int h)
{
    m_xPos = x;
    m_yPos = y;

    m_rect.x = m_xPos;
    m_rect.y = m_yPos;
    m_rect.w = w;
    m_rect.h = h;

    m_color = {255, 255, 255, 0};
    m_hoverColor = {150, 150, 150, 0};
    m_clickColor = {40, 40, 40, 0};
}

void UIButton::Update()
{
    m_hover = false;
    if (MS::x > m_xPos && MS::x < m_xPos+m_rect.w &&
        MS::y > m_yPos && MS::x < m_yPos+m_rect.h)
        m_hover = true;

    if (m_hover && MS::lBtnDown && !m_click)
    {
        Click();
        m_click = true;
    }
        
    if (!MS::lBtnDown)
        m_click = false;
}

void UIButton::Draw(SDL_Renderer* renderer)
{
    if (m_click)
        SDL_SetRenderDrawColor(renderer, m_clickColor.r, m_clickColor.g, m_clickColor.b, m_clickColor.a);
    else if (m_hover)
        SDL_SetRenderDrawColor(renderer, m_hoverColor.r, m_hoverColor.g, m_hoverColor.b, m_hoverColor.a);
    else
        SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);
}