#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class OrButton: public UIButton
{
public:
    OrButton(int x, int y):
        UIButton(x, y, 100, 50, "Or") 
    {
        UIButton::SetStaticFunc(GateHandler::AddOrGate);
    };
};
