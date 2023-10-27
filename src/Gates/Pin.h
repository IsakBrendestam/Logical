#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "MyMath.h"

class Pin
{
public:
    Pin(int xPos, int yPos, int gateId, bool isInput, int id);
    ~Pin();

    void Draw(SDL_Renderer* renderer);
    void Move(int xDiff, int yDiff);

    bool Hover(int x, int y);

    bool GetState();
    void SetState(bool state);
    int GetId();
    int GetGateId();
    int GetX();
    int GetY();

    void SetConnected(bool connected);
    bool GetConnected();

    bool IsInput();

    static int Radius();

private:
    static int radius;
    
private:
    int m_id, m_gateId;
    int m_xPos, m_yPos;
    bool m_connected;
    bool m_state;
    bool m_hover;
    bool m_isInput;
};