#pragma once

#include "GUI/UIButton.h"

class BtnButton: public UIButton
{
public:
    BtnButton(int x, int y):
        UIButton(x, y, 100, 50, "Button") 
    {
        m_func = GateHandler::AddButton;
    };
};
