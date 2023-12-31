#pragma once

#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

#include "Pin.h"

#include "MouseState.h"

using json = nlohmann::json;

class Connection
{
public:
    Connection(Pin* pin);
    ~Connection();
    
    json Save();

    void Update();
    void Draw(SDL_Renderer* renderer);

    void SetFirstPin(Pin* pin);
    void SetSecondPin(Pin* pin);

    Pin* GetFirstPin();

    void SetInPin(Pin* pin);
    Pin* GetInPin();
    void SetOutPin(Pin* pin);
    Pin* GetOutPin();

    bool IsConnected();

private:
    bool m_state;
    bool m_firstIn;
    Uint32 m_color;
    Pin* m_inPin;
    Pin* m_outPin;
};