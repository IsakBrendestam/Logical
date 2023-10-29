#pragma once

#include "GUI/UIMenu.h"

#include "GUI/ToolButtons/QuitButton.h"
#include "GUI/ToolButtons/CustomButton.h"
#include "GUI/UISelectVector.h"

#include "Utilities/FileManager.h"

#include "Debug.h"

#include <functional> 

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


        std::vector<std::string> options = FileManager::GetSaveFiles();
        UIMenu::AddSelectVector(new UISelectVector(x, y, width, height, options, 5));

        y = m_yPos + 7*m_height/8 - height/2;
        int loadBtnX = x + width/2 + btnOffset;
        auto func = std::bind(&LoadMenu::LoadClick, this);
        UIButton* btn = new CustomButton(loadBtnX, y, width/2 - btnOffset, height, func);
        UIMenu::AddButton(btn);

        // Have to be last
        m_mainBtn = new UIButton(x, bottom, width/2 - btnOffset, height, "Back");
        UIMenu::AddButton(m_mainBtn);
    };

    inline void SetSpecialBtnFunc(void (*func)()) override
    {
        m_mainBtn->SetStaticFunc(func);
    }

    inline void LoadClick()
    {
        std::string a = m_selects[0]->GetSelectedValue();
        Log(a);
    }

private:
    UIButton* m_mainBtn;
};