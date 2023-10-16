#include "UI.h"

std::vector<UIButton*> UI::m_buttons;

void UI::Initialize()
{
    CreateAndButton();
}

void UI::AddButton(int x, int y)
{
    m_buttons.push_back(new UIButton(x, y, 100, 50));
}

void UI::CreateAndButton()
{
    m_buttons.push_back(new AndButton(100, 1300));
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