#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Gate.h"
#include "Default/AndGate.h"
#include "Default/Button.h"
#include "Default/Lamp.h"
#include "Default/NotGate.h"
#include "Default/OrGate.h"
#include "Default/Clock.h"

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
    static void Deconstruct();
    static void Update(double deltaTime);
    static void Draw(SDL_Renderer* renderer);

    static void Save();

public:
    static void AddAndGate();
    static void AddOrGate();
    static void AddNotGate();
    static void AddButton();
    static void AddLamp();
    static void AddClock();

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