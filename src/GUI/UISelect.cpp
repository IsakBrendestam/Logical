#include "UISelect.h"

#include <iostream>

UISelect::UISelect(int x, int y, int w, int h, const std::string& text)
{
    m_enabled = true;

    m_text = text;

    m_xPos = x;
    m_yPos = y;

    m_rect.x = m_xPos;
    m_rect.y = m_yPos;
    m_rect.w = w;
    m_rect.h = h;

    m_color = {255, 255, 255, 0};
    m_hoverColor = {150, 150, 150, 0};
    m_clickColor = {40, 40, 40, 0};

    TTF_Font* font = TTF_OpenFont("res/fonts/font.ttf", 24);
    m_textSurface = TTF_RenderText_Solid(font, text.c_str(), {0, 0, 0}); 

    m_textRect = { m_rect.x + m_rect.w/2 - m_textSurface->w/2,
                   m_rect.y + m_rect.h/2 - m_textSurface->h/2,
                   m_rect.w,
                   m_rect.h };

    m_func = nullptr;

    m_selected = false;
}

UISelect::~UISelect()
{
    SDL_DestroyTexture(m_textTexture);
    SDL_FreeSurface(m_textSurface);
}

void UISelect::Enable()
{
    m_enabled = true;
}

void UISelect::Disable()
{
    m_enabled = false;
}

void UISelect::SetSelected(bool state)
{
    m_selected = state;
}

bool UISelect::GetSelected()
{
    return m_selected;
}

std::string UISelect::GetValue()
{
    return m_text;
}

void UISelect::Update()
{
    if (!m_enabled)
        return;

    if (MS::x > m_xPos && MS::x < m_xPos+m_rect.w &&
        MS::y > m_yPos && MS::y < m_yPos+m_rect.h &&
        (!MS::lBtnDown || m_hover))
        m_hover = true;
    else
        m_hover = false;

    if (m_hover && MS::lBtnDown && !m_click)
    {
        // Click
        m_selected = !m_selected;
        m_click = true;
    }

    if (!MS::lBtnDown)
        m_click = false; 
}

void UISelect::Draw(SDL_Renderer* renderer)
{
    if (m_selected)
        SDL_SetRenderDrawColor(renderer, m_clickColor.r, m_clickColor.g, m_clickColor.b, m_clickColor.a);
    else if (m_hover)
        SDL_SetRenderDrawColor(renderer, m_hoverColor.r, m_hoverColor.g, m_hoverColor.b, m_hoverColor.a);
    else
        SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);

    // Draw Text
    m_textTexture = SDL_CreateTextureFromSurface(renderer, m_textSurface);
    SDL_QueryTexture(m_textTexture, NULL, NULL, &m_textRect.w,&m_textRect.h);
    SDL_RenderCopy(renderer, m_textTexture, NULL, &m_textRect);
}