#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "UISelect.h"

class UISelectVector
{
public:
    UISelectVector(int x, int y, int w, int h, std::vector<std::string> options, int limit);
    ~UISelectVector();

    void Update();
    void Draw(SDL_Renderer* renderer);

    void Enable();
    void Disable();

    int GetSelectedIndex();
    std::string GetValue(int index);

    std::string GetSelectedValue();

private:
    int m_selectedIndex;
    std::vector<UISelect*> m_selects;
};