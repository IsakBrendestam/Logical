#pragma once

#include <vector>

#include "UIButton.h"
#include "../MouseState.h"

class UI
{
public:
    static void Initialize();

    static void Update(double deltaTime, MouseState ms);

    static void Draw(SDL_Renderer* renderer);

    static void CreateAndButton();

private:
    static void AddButton(int x, int y);

private:
    static std::vector<UIButton*> m_buttons;
};