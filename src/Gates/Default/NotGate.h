#pragma once

#include "Gates/Gate.h"
#include "MouseState.h"

class NotGate: public Gate
{
public:
    NotGate(int xPos, int yPos);
    void Logic() override;
};