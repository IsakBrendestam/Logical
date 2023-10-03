
#include "Debug.h"

bool Debug::SDLLogCall(const char* file, int line)
{
    while (const char* error = SDL_GetError())
    {
        std::cout << "[SDL error] (" << error << "): " <<" " << file << ":" << line << std::endl;
        return false;
    }
    return true;
};

template <typename T>
void Debug::SDLCall(T x)
{
    if (x == NULL)
        ASSERT(SDLLogCall(__FILE__, __LINE__));
};