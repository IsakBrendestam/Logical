#pragma once

#include "GUI/UIMenu.h"

#include "GUI/UIButton.h"

#include "GUI/ToolButtons/LoadButton.h"
#include "GUI/ToolButtons/SaveButton.h"
#include "GUI/ToolButtons/QuitButton.h"

class MainMenu: public UIMenu
{
public:
    MainMenu(bool startState=false): 
        UIMenu("Main Menu", startState) 
    {
        CreateButtons();
    };

    inline void CreateButtons() override
    {
        int width = m_width*0.9;
        int height = 50;

        const int btnOffset = m_width/10;
        const int bottom = m_yPos + 7*m_height/8 - height/2;

        int x = m_xPos + m_width/2 - width/2;
        int y = m_yPos + btnOffset + height;

        UIMenu::AddButton(new SaveButton(x, y, width, height));

        UIMenu::AddButton(new QuitButton(x, bottom, width, height));

        // Have to be last
        y += btnOffset + height;
        m_loadBtn = new UIButton(x, y, width, height, "Load");
        UIMenu::AddButton(m_loadBtn);
    };

    inline void SetSpecialBtnFunc(void (*func)()) override
    {
        m_loadBtn->SetFunc(func);
    }

private:
    UIButton* m_loadBtn;
};