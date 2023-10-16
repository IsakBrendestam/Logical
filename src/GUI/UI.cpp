#include "UI.h"

std::vector<UIButton*> UI::m_buttons;

void UI::Initialize()
{
    CreateButtons();
}

void UI::CreateButtons()
{
    m_buttons.push_back(new AndButton(100, 1300));
    m_buttons.push_back(new OrButton(250, 1300));
    m_buttons.push_back(new NotButton(400, 1300));
    m_buttons.push_back(new BtnButton(550, 1300));
    m_buttons.push_back(new LampButton(700, 1300));
}

void UI::Update(double deltaTime)
{
    for (auto& button : m_buttons)
        button->Update();
}

void UI::Draw(SDL_Renderer* renderer)
{
    for (auto& button : m_buttons)
        button->Draw(renderer);
}