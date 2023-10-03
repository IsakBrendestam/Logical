#pragma once

class MyMath
{
public:
    template <typename T>
    inline static T Max(T a, T b)
    {
        if (a > b)
            return a;
        return b;
    }
};