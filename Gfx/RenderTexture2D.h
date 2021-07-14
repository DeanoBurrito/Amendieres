#pragma once

#include "Renderable2D.h"
#include "RenderServerAPI.h"

namespace Amendieres::Gfx
{
    class RenderTexture2D : public Renderable2D
    {
    public:
        RenderTexture2D(const uint64_t width, const uint64_t height) 
            : RenderTexture2D(RenderServerAPI::The(), width, height) {}
        RenderTexture2D(RenderServerAPI* const api, const uint64_t width, const uint64_t height);
        RenderTexture2D(const uint64_t width, const uint64_t height, const Colour& defaultFill)
            : RenderTexture2D(RenderServerAPI::The(), width, height, defaultFill) {}
        RenderTexture2D(RenderServerAPI* const api, const uint64_t width, const uint64_t height, const Colour& defaultFill);
        RenderTexture2D(RenderServerAPI* const api, Windowing::ExtWindow* bindingWindow);

        ~RenderTexture2D();
        void Clear(const Colour& colour);
        void CopyTo(RenderTexture2D* const destination);
        bool IsValid() override;

    private:
        RenderServerAPI* server;
        uint64_t id;
    };
}