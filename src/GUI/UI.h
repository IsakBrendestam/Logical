#pragma once

#include <vector>

#include "UIButton.h"

class UI
{
public:
    static void Initialize();

    static void Update(double deltaTime);

    static void Draw(SDL_Renderer* renderer);

private:
    static void CreateButtons();

private:
    static std::vector<UIButton*> m_buttons;
};