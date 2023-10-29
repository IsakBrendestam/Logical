#include "UIMenu.h"

#include "Debug.h"

UIMenu::UIMenu(const std::string& title, bool startState)
{
    m_text = title;

    m_width = T_WIDTH/5;
    m_height = T_HEIGHT/3;

    m_xPos = T_WIDTH/2-m_width/2;
    m_yPos = T_HEIGHT/2-m_height/2;

    m_rect.x = m_xPos;
    m_rect.y = m_yPos;
    m_rect.w = m_width;
    m_rect.h = m_height;

    m_color = {100, 100, 100, 0};

    TTF_Font* font = TTF_OpenFont("res/fonts/font.ttf", 24);

    m_textSurface = TTF_RenderText_Solid(font, title.c_str(), {0, 0, 0});
    
    m_textRect = { m_rect.x + m_rect.w / 2 - m_textSurface->w/2,
                   m_rect.y + m_rect.h/12,
                   m_rect.w,
                   m_rect.h };

    m_open = startState;
}

UIMenu::~UIMenu()
{
    for (auto& btn : m_buttons)
        delete btn;

    m_buttons.erase(m_buttons.begin(), m_buttons.end());

    for (auto& sel : m_selects)
        delete sel;

    m_selects.erase(m_selects.begin(), m_selects.end());

    SDL_DestroyTexture(m_textTexture);
    SDL_FreeSurface(m_textSurface);
}

void UIMenu::Open()
{
    for (auto& btn : m_buttons)
        btn->Enable();

    for (auto& sel : m_selects)
        sel->Enable();

    m_open = true;
}

void UIMenu::Close()
{
    for (auto& btn : m_buttons)
        btn->Disable();

    for (auto& sel : m_selects)
        sel->Disable();

    m_open = false;
}

bool UIMenu::IsOpen()
{
    return m_open;
}

void UIMenu::CreateButtons()
{
}

void UIMenu::AddButton(UIButton* btn)
{
    m_buttons.push_back(btn);
}

void UIMenu::AddSelectVector(UISelectVector* sel)
{
    m_selects.push_back(sel);
}

void UIMenu::Update()
{
    if (!m_open)
        return;

    // Update Buttons
    for (auto& btn : m_buttons)
        btn->Update();

    // Update Selects
    for (auto& sel : m_selects)
        sel->Update();
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

    // Draw Selects
    for (auto& sel : m_selects)
        sel->Draw(renderer);

    // Draw Text
    m_textTexture = SDL_CreateTextureFromSurface(renderer, m_textSurface);
    SDL_QueryTexture(m_textTexture, NULL, NULL, &m_textRect.w,&m_textRect.h);
    SDL_RenderCopy(renderer, m_textTexture, NULL, &m_textRect);
}