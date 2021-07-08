#pragma once

#include <cstdint>

namespace Amendieres
{
    class Vector2i
    {
    public:
        int64_t x = 0;
        int64_t y = 0;
    };

    class Vector2f
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    #warning implement proper constructors, Zero/One constants, and some useful functions
}