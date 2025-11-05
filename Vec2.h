#pragma once

#include <iostream>

struct vec2
{
    float x, y;

    vec2(float value) { x = value; y = value; }
    vec2(float _x, float _y) { x = _x; y = _y; }

    vec2 operator+(const vec2& other) const { return vec2(x + other.x, y + other.y); }
    vec2 operator-(const vec2& other) const { return vec2(x - other.x, y - other.y); }
    vec2 operator*(const vec2& other) const { return vec2(x * other.x, y * other.y); }
    vec2 operator/(const vec2& other) const { return vec2(x / other.x, y / other.y); }
    bool operator==(const vec2& other) const { return x == other.x && y == other.y; }
    bool operator!=(const vec2& other) const { return !(*this == other); }
};
