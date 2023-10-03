#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class Connection
{
public:
    Connection(int xPos, int yPos);

    void Draw(SDL_Renderer* renderer);
    void Move(int xDiff, int yDiff);

    bool Hover(int x, int y);

    bool GetState();
    void SetState(bool state);
    int GetId();

    static int Radius();

private:
    static int id;
    static int radius;
    
private:
    int m_id;
    int m_xPos, m_yPos;
    bool m_state;
    bool m_hover;
};