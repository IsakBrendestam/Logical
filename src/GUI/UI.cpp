#include "UI.h"

std::vector<UIButton*> UI::m_buttons;

void UI::Initialize()
{
    CreateButtons();
}

void UI::CreateButtons()
{
    const int space = 150;
    int xPos = 100;
    m_buttons.push_back(new AndButton(xPos, 1300));
    xPos += space;
    m_buttons.push_back(new OrButton(xPos, 1300));
    xPos += space;
    m_buttons.push_back(new NotButton(xPos, 1300));
    xPos += space;
    m_buttons.push_back(new BtnButton(xPos, 1300));
    xPos += space;
    m_buttons.push_back(new LampButton(xPos, 1300));
    xPos += space;
    m_buttons.push_back(new ClockButton(xPos, 1300));
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