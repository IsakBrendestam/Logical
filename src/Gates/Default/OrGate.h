#pragma once

#include "Gates/Gate.h"
#include "MouseState.h"

class OrGate: public Gate
{
public:
    OrGate(int xPos, int yPos, int id = -1);
    void Logic(double deltaTime) override;
};
