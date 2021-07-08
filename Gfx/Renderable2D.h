#pragma once

#include "../Vectors.h"
#include "RenderFwd.h"

namespace Amendieres::Gfx
{
    class Renderable2D
    {
    public:
        Vector2f position;
        float rotation;

        virtual void RenderTo(RenderTexture2D* const target, RenderQueueOptions& options) {}
    };
}