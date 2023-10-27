#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <nlohmann/json.hpp>

#include <vector>
#include <string>

#include "MyMath.h"

#include "Pin.h"
#include "MouseState.h"

using json = nlohmann::json;

class Gate
{
public:
    Gate(int xPos, int yPos, int nInputs, int nOutputs, std::string type);
    ~Gate();

    virtual void Logic(double deltaTime);
    virtual void Draw(SDL_Renderer* renderer);

    virtual void Move(int x, int y);

    json Save();
    void Load(json data);

    int GetXPos();
    int GetYPos();

    int GetId();

    bool Hover(int x, int y);
    void Select(int x, int y);

    Pin* GetInputPin(int index);
    Pin* GetOutputPin(int index);
    Pin* GetSelectedPin();

    std::vector<Pin*> GetInputPins();
    std::vector<Pin*> GetOutputPins(); 

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

    std::string m_type;
};