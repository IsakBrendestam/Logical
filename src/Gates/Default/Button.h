#pragma once

#include "Gates/Gate.h"
#include "MouseState.h"

class Button: public Gate
{
public:
    Button(int xPos, int yPos);
    void Logic(MouseState ms) override;
    void Draw(SDL_Renderer* renderer) override;
private:
    bool m_hoverBtn;
    bool m_click;
    int m_btnX, m_btnY, m_btnR;
};