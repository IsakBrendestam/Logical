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

#include "ToolButtons/LoadButton.h"
#include "ToolButtons/SaveButton.h"

#include "UIMenu.h"

class UI
{
public:
    static void Initialize();
    static void Deconstruct();

    static void Update(double deltaTime);
    static void Event(SDL_Event event);
    static void Draw(SDL_Renderer* renderer);

    static bool MenuOpen();

private:
    static void CreateGateButtons();
    static void CreateToolButtons();

private:
    static std::vector<UIButton*> m_buttons;
    static UIMenu* m_menu;

    static bool escDown;
};