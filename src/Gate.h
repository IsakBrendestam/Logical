#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <vector>

#include "MouseState.h"
#include "Pin.h"

#include "MyMath.h"

class Gate
{
public:
    Gate(int xPos, int yPos, int nInputs, int nOutputs);

    virtual void Logic(MouseState ms);
    virtual void Draw(SDL_Renderer* renderer);

    virtual void Move(int x, int y);

    int GetXPos();
    int GetYPos();

    int GetId();

    bool Hover(int x, int y);
    void Select(int x, int y);

    Pin* GetInputPin(int index);
    Pin* GetOutputPin(int index);
    Pin* GetSelectedPin(MouseState ms);

private:
    void UpdateRect();
    void CreatePins(int nInputs, int nOutputs);

private:
    static int id;
    int m_id;

protected:
    int m_xPos, m_yPos;
    int m_width, m_height;
    SDL_Rect m_rect;
    SDL_Color m_color;

    bool m_moving;
    int m_offsetX, m_offsetY;

    std::vector<Pin*> m_inputs;
    std::vector<Pin*> m_outputs;

    MouseState m_ms;
};


class AndGate: public Gate
{
public:
    AndGate(int xPos, int yPos);
    void Logic(MouseState ms) override;
};

class NotGate: public Gate
{
public:
    NotGate(int xPos, int yPos);
    void Logic(MouseState ms) override;
};

class Button: public Gate
{
public:
    Button(int xPos, int yPos);
    void Logic(MouseState ms) override;
    void Draw(SDL_Renderer* renderer) override;
private:
    bool m_hoverBtn;
    bool m_click;
    int m_btnX, m_btnY, m_btnR;
};

class Lamp: public Gate
{
public:
    Lamp(int xPos, int yPos);
    void Logic(MouseState ms) override;
    void Draw(SDL_Renderer* renderer) override;
private:
    int m_lampX, m_lampY, m_lampR;
    bool m_state;
};