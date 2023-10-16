#include "Application.h"

#include "GateHandler.h"
#include "GUI/UI.h"

Application::Application(std::string title)
{
    m_title = title;

    SDL_Init(SDL_INIT_EVERYTHING);
    m_window = SDL_CreateWindow(m_title.c_str(), 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED,
                                W_WIDTH,
                                W_HEIGHT,
                                SDL_WINDOW_ALLOW_HIGHDPI);

    // Enable V-Sync
    SDL_GL_SetSwapInterval(1);

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    m_running = true;
    m_deltaTime = 0;
    m_fps = 0;
}

Application::~Application()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

int Application::Run()
{
    clock_t time1 = std::clock();
    clock_t time2 = std::clock();

    Initialize();

    bool lMouseDown = false;
    bool rMouseDown = false;

    while (m_running)
    {
        time2 = std::clock();

        m_deltaTime = (double)(time2-time1)/CLOCKS_PER_SEC;
        m_fps = 1/m_deltaTime;


        while (SDL_PollEvent(&m_windowEvent))
        {
            switch (m_windowEvent.type)
            {
                case SDL_QUIT:
                    m_running = false;
                    break;

                case SDL_KEYDOWN:
                    // Quitting if Esc is pressed
                    if (m_windowEvent.key.keysym.sym == SDLK_ESCAPE)
                        m_running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(m_windowEvent.button.button == SDL_BUTTON_LEFT)
                        lMouseDown = true;

                    if(m_windowEvent.button.button == SDL_BUTTON_RIGHT)
                        rMouseDown = true;
                    break;
                
                case SDL_MOUSEBUTTONUP:
                    if(m_windowEvent.button.button == SDL_BUTTON_LEFT)
                        lMouseDown = false;

                    if(m_windowEvent.button.button == SDL_BUTTON_RIGHT)
                        rMouseDown = false;
                    break;
            }

            Event(m_windowEvent);
        }

        m_mouseState.lBtnDown = lMouseDown;
        m_mouseState.rBtnDown = rMouseDown;
        SDL_GetMouseState(&m_mouseState.x, &m_mouseState.y); 

        MS::lBtnDown = lMouseDown;
        MS::rBtnDown = rMouseDown;
        SDL_GetMouseState(&MS::x, &MS::y); 

        if (!WINDOWS)
        {
            m_mouseState.x *= 2;
            m_mouseState.y *= 2;     

            MS::x *= 2;
            MS::y *= 2;     
        }

        Update(m_deltaTime);

        Draw();

        std::string title = m_title + " fps: " + std::to_string((int)m_fps);
        SDL_SetWindowTitle(m_window, title.c_str());
        
        // std::cout << "FPS:" << m_fps << "\r";
        // fflush(stdout);

        time1 = time2;
    }

    return EXIT_SUCCESS;
}

void Application::Initialize()
{
    UI::Initialize();

    GateHandler::Initialize();
}

void Application::Event(SDL_Event event)
{

}

void Application::Update(double deltaTime)
{
    GateHandler::Update(deltaTime, m_mouseState);

    UI::Update(deltaTime, m_mouseState);
}

void Application::Draw()
{
    SDL_RenderClear(m_renderer);

    GateHandler::Draw(m_renderer);

    UI::Draw(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 218, 215, 205, 0);
    SDL_RenderPresent(m_renderer);
}
