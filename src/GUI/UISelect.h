#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "MouseState.h"
#include "Debug.h"
#include "FileManager.h"

class UISelect
{
public:
    UISelect(int x, int y, int w, int h, const std::string& text);
    ~UISelect();
    void Draw(SDL_Renderer* renderer);
    void Update();

    void Enable();
    void Disable();

    void SetSelected(bool state);
    bool GetSelected();

    std::string GetValue();

protected:
    SDL_Color m_color, m_hoverColor, m_clickColor;
    SDL_Rect m_rect;
    std::string m_font, m_text;
    bool m_hover, m_click, m_selected;
    int m_xPos, m_yPos;
    void (*m_func)();
    SDL_Rect m_textRect;
    SDL_Surface* m_textSurface;
    SDL_Texture* m_textTexture;

    bool m_enabled;
};