#pragma once

#include "GUI/UIButton.h"
#include "Utilities/System.h"

class QuitButton: public UIButton
{
public:
    QuitButton(int x, int y, int w, int h):
        UIButton(x, y, w, h, "Quit") 
    {
        UIButton::SetStaticFunc(System::ShutDown);
    };
};