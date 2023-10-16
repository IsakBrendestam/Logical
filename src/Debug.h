#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#define DEBUG 1

#if DEBUG == 1
    #define Log(x) std::cout << x << std::endl
#else
    #define Log(x)
#endif

#define ASSERT(x) if (!(x)) throw std::invalid_argument( "received negative value" );

class Debug
{
public:
    static bool SDLLogCall(const char* file, int line);

    template <typename T>
    static void SDLCall(T x);
};

