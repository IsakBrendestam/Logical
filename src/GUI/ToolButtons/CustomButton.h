#pragma once

#include "GUI/UIButton.h"
#include "Gates/GateHandler.h"

#include <functional>

class CustomButton: public UIButton
{
public:
    CustomButton(int x, int y, int w, int h, std::function<void()> func):
        UIButton(x, y, w, h, "Load") 
    {
        m_func = func;
    };

    inline void Click() override
    {
        m_func();
    }

private:
    std::function<void()> m_func;
};