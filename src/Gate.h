#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <vector>

#include "MouseState.h"
#include "Connection.h"

#include "MyMath.h"

class Gate
{
public:
    Gate(int xPos, int yPos, int nInputs, int nOutputs);
    virtual void Logic();

    void Draw(SDL_Renderer* renderer);

    int GetXPos();
    int GetYPos();

    bool Hover(int x, int y);
    void Select(int x, int y);
    void Move(int x, int y);

private:
    void UpdateRect();
    void CreateConnections(int nInputs, int nOutputs);

protected:
    int m_xPos, m_yPos;
    int m_width, m_height;
    SDL_Rect m_rect;
    SDL_Color m_color;

    bool m_moving;
    int m_offsetX, m_offsetY;

    std::vector<Connection*> m_inputs;
    std::vector<Connection*> m_outputs;
};


class AndGate: public Gate
{
public:
    AndGate(int xPos, int yPos);
    void Logic() override;
};