#pragma once

#include <SDL2/SDL.h>

#include "Pin.h"

#include "MouseState.h"

class Connection
{
public:
    Connection(Pin* pin1);
    void Update();
    void Draw(SDL_Renderer* renderer);

    void SetPin1(Pin* pin);
    Pin* GetPin1();
    void SetPin2(Pin* pin);
    Pin* GetPin2();

    bool IsConnected();

private:
    bool m_state;
    Uint32 m_color;
    Pin* m_pin1;
    Pin* m_pin2;
};