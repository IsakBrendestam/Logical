#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class DisplayButton: public UIButton
{
public:
    DisplayButton(int x, int y):
        UIButton(x, y, 100, 50, "Display")
    {
        m_func = GateHandler::AddDisplay;   
    };
};