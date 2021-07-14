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

        virtual ~Renderable2D() {};

        virtual bool IsValid() = 0;
        virtual void RenderTo(RenderTexture2D* const target, RenderQueueOptions& options) {}
    };
}