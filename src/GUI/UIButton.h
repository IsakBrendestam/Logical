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