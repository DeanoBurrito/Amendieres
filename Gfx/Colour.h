#pragma once

#include <cstdint>

namespace Amendieres::Gfx
{
    enum class ColourPackingOrder
    {
        RGBA,
        ARGB,
        BGRA,
        ABGR,
    };
    
    class Colour
    {
    public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Colour() : Colour(0xFFFFFFFF) {}
        Colour(uint32_t rgba)
        {
            r = (0xFF000000 & rgba) >> 24;
            g = (0x00FF0000 & rgba) >> 16;
            b = (0x0000FF00 & rgba) >> 8;
            a = (0x000000FF & rgba);
        }
        Colour(uint8_t red, uint8_t green, uint8_t blue)
        : r(red), g(green), b(blue), a(255) {}
        Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
        : r(red), g(green), b(blue), a(alpha) {}

        uint32_t GetPacked(ColourPackingOrder order = ColourPackingOrder::RGBA) const;
    private:
    };
}