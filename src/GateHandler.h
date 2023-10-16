#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Gate.h"
#include "MouseState.h"
#include "Connection.h"

enum State{
    DEFAULT,
    CONNECTING,
    RESETTING
};

class GateHandler
{
public:
    static void Initialize();
    static void Update(double deltaTime, MouseState ms);
    static void Draw(SDL_Renderer* renderer);

    static void AddAndGate();

private:
    static void CheckGateSelection(MouseState ms, int idnex);
    static void HandleGateMovement(MouseState ms, int index);
    static void CreateConnection(MouseState ms);
    static void CloseConnection(MouseState ms);
    static void HandleConnections(MouseState ms);

private:
    static int m_movingGateIndex;
    static std::vector<Gate*> m_gates;
    static std::vector<Connection*> m_connections;
    static State m_state;
    static Connection* m_tempConnection;
};