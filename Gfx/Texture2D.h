#pragma once

#include "RenderServerAPI.h"
#include "Renderable2D.h"

namespace Amendieres::Gfx
{
    class Texture2D : public Renderable2D
    {
    public:
        Texture2D(RenderServerAPI* api);

    private:
        RenderServerAPI* server;
    };
}