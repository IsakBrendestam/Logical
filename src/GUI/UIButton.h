#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>

#include "MouseState.h"
#include "Debug.h"
#include "FileManager.h"


class UIButton
{
public:
    UIButton(int x, int y, int w, int h, const std::string& text);
    ~UIButton();
    void Draw(SDL_Renderer* renderer);
    void Update();

    void Enable();
    void Disable();

    inline void SetStaticFunc(void (*func)())
    {
        m_func = func;
    };

    inline virtual void Click() 
    {
        if (m_func != nullptr)
            m_func();
    };

protected:
    SDL_Color m_color, m_hoverColor, m_clickColor;
    SDL_Rect m_rect;
    std::string m_font, m_text;
    bool m_hover, m_click;
    int m_xPos, m_yPos;
    void (*m_func)();
    SDL_Rect m_textRect;
    SDL_Surface* m_textSurface;
    SDL_Texture* m_textTexture;

    bool m_enabled;
};