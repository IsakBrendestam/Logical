#pragma once

#include "GUI/UIButton.h"

class LampButton: public UIButton
{
public:
    LampButton(int x, int y):
        UIButton(x, y, 100, 50, "Lamp") 
    {
        m_func = GateHandler::AddLamp;
    };
};