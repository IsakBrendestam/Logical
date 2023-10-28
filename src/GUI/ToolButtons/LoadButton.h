#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class LoadButton: public UIButton
{
public:
    LoadButton(int x, int y, int w, int h):
        UIButton(x, y, w, h, "Load") 
    {
        UIButton::SetFunc(GateHandler::Load);
    };
};