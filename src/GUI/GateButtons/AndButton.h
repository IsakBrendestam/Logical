#pragma once

#include "GUI/UIButton.h"

class AndButton: public UIButton
{
public:
    AndButton(int x, int y):
        UIButton(x, y, 100, 50, "And") 
    {
        m_func = GateHandler::AddAndGate;
    };
};