#pragma once
#include "C:\SDL\include\SDL3\SDL_stdinc.h"

struct vector2
{
    float X, Y;

    inline vector2() = default;
    inline vector2(const float x, const float y)
    {
        X = x; Y = y;
    }

    vector2 operator*(float a) {
        return vector2(X * a, Y * a);
    }

    float Length() {
        return SDL_sqrtf(X*X + Y*Y);
    }
    void Normalize() {
        float l = Length();
        if (l <= 0) return;
        X = X / l;
        Y = Y / l;
    }
};

struct vector3
{
    float X, Y, Z;

    inline vector3() = default;
    inline vector3(const float x, const float y, const float z)
    {
        X = x; Y = y; Z = z;
    }
};