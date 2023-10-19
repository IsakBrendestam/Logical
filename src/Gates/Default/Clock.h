#pragma once

#include "Gates/Gate.h"
#include "MouseState.h"

class Clock: public Gate
{
public:
    Clock(int xPos, int yPos, int interval);
    void Logic(double deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;
private:
    double m_timeSinceChange;
    double m_interval;
    int m_btnX, m_btnY, m_btnR;
    bool m_state;
};