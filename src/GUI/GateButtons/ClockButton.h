#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class ClockButton: public UIButton
{
public:
    ClockButton(int x, int y):
        UIButton(x, y, 100, 50, "Clock")
    {
        UIButton::SetFunc(GateHandler::AddClock);
    };
};