#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Gates/Gate.h"
#include "Gates/Default/AndGate.h"
#include "Gates/Default/Button.h"
#include "Gates/Default/Lamp.h"
#include "Gates/Default/NotGate.h"
#include "Gates/Default/OrGate.h"

#include "Connection.h"
#include "MouseState.h"

enum State{
    DEFAULT,
    CONNECTING,
    RESETTING,
    MOVING
};

class GateHandler
{
public:
    static void Initialize();
    static void Update(double deltaTime);
    static void Draw(SDL_Renderer* renderer);

    static void AddAndGate();
    static void AddOrGate();
    static void AddNotGate();
    static void AddButton();
    static void AddLamp();

private:
    static void CheckGateSelection(int idnex);
    static void HandleGateMovement(int index);
    static void RemoveGate();
    static void CreateConnection();
    static void CloseConnection();
    static void HandleConnections();

private:
    static int m_movingGateIndex;
    static int m_removeGateIndex;
    static std::vector<Gate*> m_gates;
    static std::vector<Connection*> m_connections;
    static State m_state;
    static Connection* m_tempConnection;
};