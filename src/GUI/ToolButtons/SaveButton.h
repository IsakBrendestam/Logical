#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class SaveButton: public UIButton
{
public:
    SaveButton(int x, int y):
        UIButton(x, y, 100, 70, "Save") 
    {
        m_func = GateHandler::Save;
    };
};