#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class BtnButton: public UIButton
{
public:
    BtnButton(int x, int y):
        UIButton(x, y, 100, 50, "Button") 
    {
        UIButton::SetFunc(GateHandler::AddButton);
    };
};
