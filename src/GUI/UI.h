#pragma once

#include <vector>

#include "UIButton.h"
#include "GateButtons/AndButton.h"
#include "GateButtons/BtnButton.h"
#include "GateButtons/ClockButton.h"
#include "GateButtons/DisplayButton.h"
#include "GateButtons/LampButton.h"
#include "GateButtons/NotButton.h"
#include "GateButtons/OrButton.h"

class UI
{
public:
    static void Initialize();
    static void Deconstruct();

    static void Update(double deltaTime);

    static void Draw(SDL_Renderer* renderer);

private:
    static void CreateButtons();

private:
    static std::vector<UIButton*> m_buttons;
};