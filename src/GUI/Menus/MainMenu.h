#pragma once

#include "GUI/UIMenu.h"

#include "GUI/ToolButtons/QuitButton.h"

class MainMenu: public UIMenu
{
public:
    MainMenu(): 
        UIMenu("Main Menu") 
    {
        CreateButtons();
    };

    inline void CreateButtons() override
    {
        const int btnOffset = m_width/10;
        int width = m_width*0.9;
        int height = 50;
        int x = m_xPos + m_width/2 - width/2;
        int y = m_yPos + btnOffset + height;

        UIMenu::AddButton(new SaveButton(x, y, width, height));

        y += btnOffset + height;
        UIMenu::AddButton(new LoadButton(x, y, width, height));

        y = m_yPos + 7*m_height/8 - height/2;
        UIMenu::AddButton(new QuitButton(x, y, width, height));
    };
};