#include "UIMenu.h"

UIMenu::UIMenu(const std::string& text)
{
    int width = T_WIDTH/5;
    int height = T_HEIGHT/3;

    m_xPos = T_WIDTH/2-width/2;
    m_yPos = T_HEIGHT/2-height/2;

    m_rect.x = m_xPos;
    m_rect.y = m_yPos;
    m_rect.w = width;
    m_rect.h = height;

    m_textRect = { m_rect.x,
                   m_rect.y + m_rect.h/4,
                   m_rect.w,
                   m_rect.h };

    m_color = {255, 255, 255, 0};

    TTF_Font* font = TTF_OpenFont("res/fonts/font.ttf", 24);

    m_textSurface = TTF_RenderText_Solid(font, text.c_str(), {0, 0, 0});

    m_open = false;
}

UIMenu::~UIMenu()
{
    SDL_DestroyTexture(m_textTexture);
    SDL_FreeSurface(m_textSurface);
}

void UIMenu::Open()
{
    for (auto& btn : m_buttons)
        btn->Enable();

    m_open = true;
}

void UIMenu::Close()
{
    for (auto& btn : m_buttons)
        btn->Disable();

    m_open = false;
}

bool UIMenu::IsOpen()
{
    return m_open;
}

void UIMenu::Update()
{
    if (!m_open)
        return;

    for (auto& btn : m_buttons)
        btn->Update();
}

void UIMenu::Draw(SDL_Renderer* renderer)
{
    if (!m_open)
        return;

    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);

    // Draw Buttons
    for (auto& btn : m_buttons)
        btn->Draw(renderer);

    // Draw Text
    m_textTexture = SDL_CreateTextureFromSurface(renderer, m_textSurface);
    SDL_QueryTexture(m_textTexture, NULL, NULL, &m_textRect.w,&m_textRect.h);
    SDL_RenderCopy(renderer, m_textTexture, NULL, &m_textRect);
}