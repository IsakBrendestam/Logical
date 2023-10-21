#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <string>

#include "MouseState.h"

#define W_WIDTH 700
#define W_HEIGHT 700

#define WINDOWS false

#if defined(_WIN64) || defined(_WIN32)
    #define T_WIDTH W_WIDTH
    #define T_HEIGHT W_HEIGHT
    #define WINDOWS true
#elif __APPLE__
    #define T_WIDTH W_WIDTH*2
    #define T_HEIGHT W_HEIGHT*2
    #define WINDOWS false
#elif defined(linux)
    #define T_WIDTH W_WIDTH
    #define T_HEIGHT W_HEIGHT
    #define WINDOWS true
#endif

class Application
{
public:
    Application(std::string title);
    ~Application();

    int Run();
    void Initialize();
    void Deconstruct();
    void Event(SDL_Event event);
    void Update(double deltaTime);
    void Draw();

private:
    std::string m_title;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Event m_windowEvent;

    bool m_running;
    double m_deltaTime;
    double m_fps;

private:
};