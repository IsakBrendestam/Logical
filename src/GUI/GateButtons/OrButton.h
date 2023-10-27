#pragma once

#include "GUI/UIButton.h"

class OrButton: public UIButton
{
public:
    OrButton(int x, int y):
        UIButton(x, y, 100, 50, "Or") 
    {
        m_func = GateHandler::AddOrGate;
    };
};
