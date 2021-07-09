#pragma once

#include <cstdint>

namespace Amendieres
{
    class Vector2i
    {
    public:
        int64_t x;
        int64_t y;

        Vector2i() : x(0), y(0) {}
        Vector2i(int64_t xy) : x(xy), y(xy) {}
        Vector2i(int64_t x, int64_t y) : x(x), y(y) {}
    };

    class Vector2f
    {
        float x;
        float y;

        Vector2f() : x(0.0f), y(0.0f) {}
        Vector2f(float xy) : x(xy), y(xy) {}
        Vector2f(float x, float y) : x(x), y(y) {}
    };
}