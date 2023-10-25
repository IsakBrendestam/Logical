#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>

#include "MouseState.h"
#include "Debug.h"
#include "FileManager.h"

#include "Gates/GateHandler.h"

class UIButton
{
public:
    UIButton(int x, int y, int w, int h, const std::string& text);
    ~UIButton();
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
    SDL_Rect m_textRect;
    SDL_Surface* m_textSurface;
    SDL_Texture* m_textTexture;
};

class AndButton: public UIButton
{
public:
    AndButton(int x, int y):
        UIButton(x, y, 100, 50, "And") 
    {
        m_func = GateHandler::AddAndGate;
    };
};

class OrButton: public UIButton
{
public:
    OrButton(int x, int y):
        UIButton(x, y, 100, 50, "Or") 
    {
        m_func = GateHandler::AddOrGate;
    };
};

class NotButton: public UIButton
{
public:
    NotButton(int x, int y):
        UIButton(x, y, 100, 50, "Not") 
    {
        m_func = GateHandler::AddNotGate;
    };
};

class BtnButton: public UIButton
{
public:
    BtnButton(int x, int y):
        UIButton(x, y, 100, 50, "Button") 
    {
        m_func = GateHandler::AddButton;
    };
};

class LampButton: public UIButton
{
public:
    LampButton(int x, int y):
        UIButton(x, y, 100, 50, "Lamp") 
    {
        m_func = GateHandler::AddLamp;
    };
};

class ClockButton: public UIButton
{
public:
    ClockButton(int x, int y):
        UIButton(x, y, 100, 50, "Clock")
    {
        m_func = GateHandler::AddClock;   
    };
};

class DisplayButton: public UIButton
{
public:
    DisplayButton(int x, int y):
        UIButton(x, y, 100, 50, "Display")
    {
        m_func = GateHandler::AddDisplay;   
    };
};