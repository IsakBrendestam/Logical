#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Constants.h"
#include "MouseState.h"
#include "Debug.h"
#include "FileManager.h"

#include "Gates/GateHandler.h"

#include "UIButton.h"
#include "ToolButtons/LoadButton.h"
#include "ToolButtons/SaveButton.h"
#include "ToolButtons/QuitButton.h"

class UIMenu
{
public:
    UIMenu(const std::string& text);
    ~UIMenu();

    void Open();
    void Close();

    bool IsOpen();

    void Draw(SDL_Renderer* renderer);
    void Update();

protected:
    bool m_open;
    int m_xPos, m_yPos;
    SDL_Color m_color;
    SDL_Rect m_rect;
    SDL_Rect m_textRect;
    std::string m_font, m_text;
    SDL_Surface* m_textSurface;
    SDL_Texture* m_textTexture;

    std::vector<UIButton*> m_buttons;
};