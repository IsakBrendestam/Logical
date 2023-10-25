#pragma once

#include "Gates/Gate.h"
#include "MouseState.h"

class Display: public Gate
{
public:
    Display(int xPos, int yPos);
    void Logic(double deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;
private:
    void SetPositions();
private:
    int m_value;
    const int m_nSegments = 7;
    SDL_Rect m_segments[7];
    SDL_Color m_segmentOnColor, m_segmentOffColor;
    bool m_segmentStates[7];
};