#pragma once

#include "RenderServerAPI.h"
#include "Renderable2D.h"

namespace Amendieres::Gfx
{
    class Texture2D : public Renderable2D
    {
    public:
        Texture2D(const uint64_t w, const uint64_t h) 
            : Texture2D(RenderServerAPI::The(), w, h) {};
        Texture2D(RenderServerAPI* const api, const uint64_t w, const uint64_t h);
        Texture2D(const uint64_t w, const uint64_t h, const uint32_t* rgba32Data, const uint64_t dataLength)
            : Texture2D(RenderServerAPI::The(), w, h, rgba32Data, dataLength) {};
        Texture2D(RenderServerAPI* const api, const uint64_t w, const uint64_t h, const uint32_t* rgba32Data, const uint64_t dataLength);

    private:
        RenderServerAPI* server;
    };
}