#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Constants.h"
#include "MouseState.h"
#include "Debug.h"
#include "FileManager.h"

#include "Gates/GateHandler.h"

#include "UIButton.h"
#include "UISelectVector.h"

class UIMenu
{
public:
    UIMenu(const std::string& title, bool startState=false);
    ~UIMenu();

    void Open();
    void Close();

    bool IsOpen();

    void Draw(SDL_Renderer* renderer);
    void Update();
    
    inline virtual void SetSpecialBtnFunc(void (*func)()) {};

protected:
    virtual void CreateButtons();
    void AddButton(UIButton* btn);
    void AddSelectVector(UISelectVector* sel);

protected:
    bool m_open;
    int m_xPos, m_yPos;
    int m_width, m_height;
    SDL_Color m_color;
    SDL_Rect m_rect;
    SDL_Rect m_textRect;
    std::string m_font, m_text;
    SDL_Surface* m_textSurface;
    SDL_Texture* m_textTexture;

    std::vector<UIButton*> m_buttons;
    std::vector<UISelectVector*> m_selects;
};