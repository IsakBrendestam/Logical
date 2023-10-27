#pragma once

#include "Gates/Gate.h"
#include "MouseState.h"

class AndGate: public Gate
{
public:
    AndGate(int xPos, int yPos, int id = -1);
    void Logic(double deltaTime) override;
};
