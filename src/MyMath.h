#pragma once

class MyMath
{
public:

    inline static bool Max(bool a, bool b)
    {
        if (a == true)
            return a;
        return b;
    }

    template <typename T>
    inline static T Max(T a, T b)
    {
        if (a > b)
            return a;
        return b;
    }

    template <typename T>
    inline static T Pow(T a)
    {
        return a*a;
    }
};