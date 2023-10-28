#pragma once

#include "GUI/UIButton.h"
#include "Utilities/System.h"

class QuitButton: public UIButton
{
public:
    QuitButton(int x, int y):
        UIButton(x, y, 100, 70, "Quit") 
    {
        m_func = System::ShutDown;
    };
};