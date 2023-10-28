#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class NotButton: public UIButton
{
public:
    NotButton(int x, int y):
        UIButton(x, y, 100, 50, "Not") 
    {
        m_func = GateHandler::AddNotGate;
    };
};