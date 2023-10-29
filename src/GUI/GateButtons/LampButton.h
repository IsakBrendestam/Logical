#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class LampButton: public UIButton
{
public:
    LampButton(int x, int y):
        UIButton(x, y, 100, 50, "Lamp") 
    {
        UIButton::SetStaticFunc(GateHandler::AddLamp);
    };
};