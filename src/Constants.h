
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