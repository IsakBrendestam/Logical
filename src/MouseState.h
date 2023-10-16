#pragma once

struct MouseState{
    int x;
    int y;
    bool rBtnDown;
    bool lBtnDown;
};

class MS{
public:
    static int x;
    static int y;
    static bool rBtnDown;
    static bool lBtnDown;
};

