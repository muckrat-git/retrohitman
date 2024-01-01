#pragma once

#include "Vec2.cpp"
#include <stdint.h>

#define cstr const char *

template<typename a, typename b>
struct Pair {
    a first;
    b second;
};