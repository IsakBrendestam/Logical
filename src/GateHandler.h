#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Gate.h"
#include "MouseState.h"

class GateHandler
{
public:
    static void Initialize();
    static void Update(double deltaTime, MouseState ms);
    static void Draw(SDL_Renderer* renderer);

private:
    static void CheckGateSelection(MouseState ms, int idnex);
    static void HandleGateMovement(MouseState ms, int index);

private:
    static int m_movingGateIndex;
    static std::vector<Gate*> m_gates;
};