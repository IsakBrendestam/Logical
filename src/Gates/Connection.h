#pragma once

#include <SDL2/SDL.h>

#include "MouseState.h"
#include "Pin.h"

class Connection
{
public:
    Connection(Pin* pin1);
    void Update(MouseState ms);
    void Draw(SDL_Renderer* renderer);

    void SetPin1(Pin* pin);
    Pin* GetPin1();
    void SetPin2(Pin* pin);
    Pin* GetPin2();

    bool IsConnected();

private:
    bool m_state;
    Uint32 m_color;
    MouseState m_ms;
    Pin* m_pin1;
    Pin* m_pin2;
};