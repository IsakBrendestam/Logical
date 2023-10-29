#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

#include <functional>

class LoadButton: public UIButton
{
public:
    LoadButton(int x, int y, int w, int h):
        UIButton(x, y, w, h, "Load") 
    {
        UIButton::SetStaticFunc(GateHandler::Load);
    };
};