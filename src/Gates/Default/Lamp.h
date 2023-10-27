#pragma once

#include "Gates/Gate.h"
#include "MouseState.h"

class Lamp: public Gate
{
public:
    Lamp(int xPos, int yPos, int id = -1);
    void Logic(double deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;
private:
    int m_lampX, m_lampY, m_lampR;
    bool m_state;
};