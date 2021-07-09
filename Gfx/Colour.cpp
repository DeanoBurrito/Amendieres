#include "Colour.h"

namespace Amendieres::Gfx
{
    uint32_t Colour::GetPacked(ColourPackingOrder order) const
    {
        uint32_t data = 0;
        switch (order)
        {
        case ColourPackingOrder::RGBA:
            {
                data |= (uint32_t)r << 24;
                data |= (uint32_t)g << 16;
                data |= (uint32_t)b << 8;
                data |= (uint32_t)a;
                return data;
            }

        case ColourPackingOrder::ARGB:
            {
                data |= (uint32_t)a << 24;
                data |= (uint32_t)r << 16;
                data |= (uint32_t)g << 8;
                data |= (uint32_t)b;
                return data;
            }

        case ColourPackingOrder::BGRA:
            {
                data |= (uint32_t)b << 24;
                data |= (uint32_t)g << 16;
                data |= (uint32_t)r << 8;
                data |= (uint32_t)a;
                return data;
            }

        case ColourPackingOrder::ABGR:
            {   
                data |= (uint32_t)a << 24;
                data |= (uint32_t)b << 16;
                data |= (uint32_t)g << 8;
                data |= (uint32_t)r;
                return data;
            }
        }
    }
}