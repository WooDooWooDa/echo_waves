#pragma once
#include "C:\SDL\include\SDL3\SDL_stdinc.h"
#include <string>

struct vector2
{
    float X, Y;

    inline vector2() {
        X = Y = 0;
    }

    inline vector2(float x) {
        X = Y = x;
    }

    inline vector2(const float x, const float y)
    {
        X = x; Y = y;
    }

    vector2 operator*(float a) {
        return vector2(X * a, Y * a);
    }

    vector2 operator*(const vector2& b) {
        return vector2(X * b.X, Y * b.Y);
    }
    
    vector2 operator/(float b) {
        return vector2(X / b, Y / b);
    }

    float dot(const vector2& b) const {
        return (this->X * b.X) + (this->Y * b.Y);
    }

    vector2 operator-(const vector2& b) {
        return vector2(X - b.X, Y - b.Y);
    }

    vector2 operator+(const vector2& b) {
        return vector2(X + b.X, Y + b.Y);
    }

    bool operator==(const vector2& other) const {
        return X == other.X && Y == other.Y;
    }

    std::string ToString() const
    {
        return "(x = " + std::to_string(X) + ", Y = " + std::to_string(Y) + ")";
    }

    float Length() const {
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

    inline vector3() {
        X = Y = Z = 0;
    }
    inline vector3(const float x, const float y, const float z)
    {
        X = x; Y = y; Z = z;
    }
};

struct RGBColor {
    float R, G, B, A;

    inline RGBColor() {
        R = G = B = A = 0;
    }
    inline RGBColor(const float r, const float g, const float b)
    {
        R = r; G = g; B = b;
        A = 255;
    }
    inline RGBColor(const float r, const float g, const float b, const float a) : RGBColor(r,g,b)
    {
        A = a;
    }
};

#define COLOR_WHITE         RGBColor(255, 255, 255)
#define COLOR_RED           RGBColor(255, 0, 0)