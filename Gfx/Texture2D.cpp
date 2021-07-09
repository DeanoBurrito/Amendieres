#include "../Debug.h"
#include "Texture2D.h"

namespace Amendieres::Gfx
{
    Texture2D::Texture2D(RenderServerAPI* api)
    {
        if (api == nullptr)
        {
            LOG_ERROR("Attempting to create Texture2D with api ptr set to null!");
        }

        server = api;
    }
}