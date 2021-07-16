#pragma once

#include "RenderServerAPI.h"

namespace Amendieres::Gfx
{
    class DynamicFont
    {
    public:
        DynamicFont(const char* const fontData, const uint64_t dataLength) 
            : DynamicFont(RenderServerAPI::The(), fontData, dataLength) {}
        DynamicFont(RenderServerAPI* const api, const char* const fontData, const uint64_t dataLength);
        DynamicFont(const char* const fontData, const uint64_t dataLength, const uint8_t fontSize)
            : DynamicFont(RenderServerAPI::The(), fontData, dataLength, fontSize) {}
        DynamicFont(RenderServerAPI* const api, const char* const fontData, const uint64_t dataLength, const uint8_t fontSize);

        ~DynamicFont();
    private:
        RenderServerAPI* server;
        uint64_t id;
    };
}