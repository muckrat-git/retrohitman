#pragma once

#include "Vec2.cpp"
#include <stdint.h>

// C String shorthand
#define cstr const char *

// Mod 1 shorthand
#define modf0(x) (x - floorf(x))

// Unsigned char and short shorthands
#define u8 unsigned char
#define u16 unsigned short

// Multipurpose 'Pair' structure
template<typename a, typename b>
struct Pair {
    a first;
    b second;
};

// Vec2 based rectangle structure
template<typename x>
struct Rect {
    Vec2<x> position;
    Vec2<x> size;
};

// Floating point modulo equation
float Modf(float a, float n) {
    return a - floor(a/n) * n;
}

// Rotary distance equation
float RotaryDistance(float a, float b) {
    return abs(Modf(a - b + PI, PI * 2) - PI);
}

// Rotary linear interpolation equation
float RotaryLerp(float a, float b, float x) {
    return atan2((1 - x) * sinf(a) + x * sinf(b), (1-x) * cosf(a) + x * cosf(b));
}

// Restricts the values available to 'count' amount
float Quantize(float value, float count, float min, float max) {
    float normal = Normalize(value, min, max);
    return roundf(normal * count) * max / count + min;
}