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

struct vec3
{
    float x, y, z;

    vec3(float value = 0.0f) : x(value), y(value), z(value) {}
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    vec3 operator+(const vec3& other) const { return vec3(x + other.x, y + other.y, z + other.z); }
    vec3 operator-(const vec3& other) const { return vec3(x - other.x, y - other.y, z - other.z); }
    vec3 operator*(const vec3& other) const { return vec3(x * other.x, y * other.y, z * other.z); }
    vec3 operator/(const vec3& other) const { return vec3(x / other.x, y / other.y, z / other.z); }
    bool operator==(const vec3& other) const { return x == other.x && y == other.y && z == other.z; }
    bool operator!=(const vec3& other) const { return !(*this == other); }
};

struct vec4
{
    float x, y, z, w;

    vec4(float value = 0.0f) : x(value), y(value), z(value), w(value) {}
    vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

    vec4 operator+(const vec4& other) const { return vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
    vec4 operator-(const vec4& other) const { return vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
    vec4 operator*(const vec4& other) const { return vec4(x * other.x, y * other.y, z * other.z, w * other.w); }
    vec4 operator/(const vec4& other) const { return vec4(x / other.x, y / other.y, z / other.z, w / other.w); }
    bool operator==(const vec4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
    bool operator!=(const vec4& other) const { return !(*this == other); }
};
