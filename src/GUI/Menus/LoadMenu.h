#pragma once

#include "GUI/UIMenu.h"

#include "GUI/ToolButtons/QuitButton.h"

class LoadMenu: public UIMenu
{
public:
    LoadMenu(bool startState=false): 
        UIMenu("Load Menu", startState) 
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


        // Have to be last
        y = m_yPos + 7*m_height/8 - height/2;
        m_mainBtn = new UIButton(x, bottom, width, height, "Back");
        UIMenu::AddButton(m_mainBtn);
    };

    inline void SetSpecialBtnFunc(void (*func)()) override
    {
        m_mainBtn->SetFunc(func);
    }

private:
    UIButton* m_mainBtn;
};