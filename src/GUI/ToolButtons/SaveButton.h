#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

class SaveButton: public UIButton
{
public:
    SaveButton(int x, int y, int w, int h):
        UIButton(x, y, w, h, "Save") 
    {
        UIButton::SetStaticFunc(GateHandler::Save);
    };
};