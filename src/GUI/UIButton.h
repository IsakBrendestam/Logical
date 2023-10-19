#pragma once

#include <SDL2/SDL.h>
#include <functional>

#include "MouseState.h"
#include "Debug.h"
#include "FileManager.h"

#include "Gates/GateHandler.h"

class UIButton
{
public:
    UIButton(int x, int y, int w, int h);
    void Draw(SDL_Renderer* renderer);
    void Update();

    inline void Click() {
        m_func();
    };

protected:
    SDL_Color m_color, m_hoverColor, m_clickColor;
    SDL_Rect m_rect;
    std::string m_font;
    bool m_hover, m_click;
    int m_xPos, m_yPos;
    void (*m_func)();
};

class AndButton: public UIButton
{
public:
    AndButton(int x, int y):
        UIButton(x, y, 100, 50) 
    {
        m_func = GateHandler::AddAndGate;
    };
};

class OrButton: public UIButton
{
public:
    OrButton(int x, int y):
        UIButton(x, y, 100, 50) 
    {
        m_func = GateHandler::AddOrGate;
    };
};

class NotButton: public UIButton
{
public:
    NotButton(int x, int y):
        UIButton(x, y, 100, 50) 
    {
        m_func = GateHandler::AddNotGate;
    };
};

class BtnButton: public UIButton
{
public:
    BtnButton(int x, int y):
        UIButton(x, y, 100, 50) 
    {
        m_func = GateHandler::AddButton;
    };
};

class LampButton: public UIButton
{
public:
    LampButton(int x, int y):
        UIButton(x, y, 100, 50) 
    {
        m_func = GateHandler::AddLamp;
    };
};

class ClockButton: public UIButton
{
public:
    ClockButton(int x, int y):
        UIButton(x, y, 100, 50)
    {
        m_func = GateHandler::AddClock;   
    };
};