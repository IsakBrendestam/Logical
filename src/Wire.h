#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "Connection.h"

class Wire
{
public:
    Wire(Connection* connection1, Connection* connection2 = nullptr);

    void UpdateConnection(Connection* thisConnection);
    void Draw();
    
private:
    Connection m_connection1, m_connection2;
};