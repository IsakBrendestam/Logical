#pragma once

#include <SDL2/SDL.h>
#include <string>


#if __APPLE__
    #define CPY_KEY 1024
#else
    #define CPY_KEY KMOD_CTRL
#endif

class InputHandler
{
public:
    static void Event(SDL_Event event);
    static void Reset();

    static std::string GetInput();

private:
    static std::string m_inputText;
};
