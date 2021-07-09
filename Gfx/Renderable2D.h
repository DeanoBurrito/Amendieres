#pragma once

#include "../Vectors.h"
#include "RenderFwd.h"
#include "Colour.h"

namespace Amendieres::Gfx
{
    class Renderable2D
    {
    public:
        Vector2f position;
        Vector2f scale;
        float rotation;
        Colour tint;

        virtual void RenderTo(RenderTexture2D* const target, RenderQueueOptions& options) {}
    };
}