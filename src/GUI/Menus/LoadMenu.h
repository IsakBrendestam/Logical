#pragma once

#include "GUI/UIMenu.h"

#include "GUI/ToolButtons/QuitButton.h"

class LoadMenu: public UIMenu
{
public:
    LoadMenu(bool startState=false): 
        UIMenu("Main Menu", startState) 
    {
        CreateButtons();
    };

    inline void CreateButtons() override
    {
        
    };
};