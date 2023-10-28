#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <string>

#include "MouseState.h"
#include "Constants.h"
#include "Utilities/System.h"

enum EngineState 
{
    RUNNING,
    MENU
};

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
    EngineState m_state;
};