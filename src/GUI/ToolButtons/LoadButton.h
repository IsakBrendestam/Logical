#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class LoadButton: public UIButton
{
public:
    LoadButton(int x, int y):
        UIButton(x, y, 100, 70, "Load") 
    {
        m_func = GateHandler::Load;
    };
};