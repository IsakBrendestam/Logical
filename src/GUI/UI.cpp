#include "UI.h"

std::vector<UIButton*> UI::m_buttons;
UIMenu* UI::m_menu;
bool UI::escDown;

void UI::Initialize()
{
    escDown = false;

    CreateToolButtons();
    CreateGateButtons();

    m_menu = new MainMenu();
}

void UI::Deconstruct()
{
    for (auto& button : m_buttons)
        delete button;
}

void UI::CreateGateButtons()
{
    const int space = 150;
    const int yPos = 1300;
    int xPos = 100;

    m_buttons.push_back(new AndButton(xPos, yPos));
    xPos += space;
    m_buttons.push_back(new OrButton(xPos, yPos));
    xPos += space;
    m_buttons.push_back(new NotButton(xPos, yPos));
    xPos += space;
    m_buttons.push_back(new BtnButton(xPos, yPos));
    xPos += space;
    m_buttons.push_back(new LampButton(xPos, yPos));
    xPos += space;
    m_buttons.push_back(new ClockButton(xPos, yPos));
    xPos += space;
    m_buttons.push_back(new DisplayButton(xPos, yPos));
}

void UI::CreateToolButtons()
{
    const int space = 150;
    const int yPos = 50;
    int xPos = 1000;

    m_buttons.push_back(new SaveButton(xPos, yPos, 100, 50));
    xPos += space;
    m_buttons.push_back(new LoadButton(xPos, yPos, 100, 50));
}

bool UI::MenuOpen()
{
    return m_menu->IsOpen();
}

void UI::Event(SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                if (!escDown)
                {
                    if (m_menu->IsOpen())
                        m_menu->Close();
                    else
                        m_menu->Open();
                }
                escDown = true;
            }

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                escDown = false;
        
            break;
    
    }
}

void UI::Update(double deltaTime)
{
    m_menu->Update();

    if (!m_menu->IsOpen())
        for (auto& button : m_buttons)
            button->Update();
}

void UI::Draw(SDL_Renderer* renderer)
{
    m_menu->Draw(renderer);

    for (auto& button : m_buttons)
        button->Draw(renderer);
}