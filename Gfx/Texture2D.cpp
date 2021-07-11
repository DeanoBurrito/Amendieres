#include "../Debug.h"
#include "Texture2D.h"

namespace Amendieres::Gfx
{
    Texture2D::Texture2D(RenderServerAPI* const api, const uint64_t w, const uint64_t h)
    {
        if (api == nullptr)
            LOG_ERROR("Attempting to create Texture2D with null RenderServer ptr.");
        server = api;

        id = server->Texture2D_Create(this, w, h);
    }

    Texture2D::Texture2D(RenderServerAPI* const api, const uint64_t w, const uint64_t h, const uint32_t* const rgba32Data, const uint64_t dataLength)
    {
        if (api == nullptr)
            LOG_ERROR("Attempting to create Texture2D with null RenderServer ptr.");
        server = api;

        id = server->Texture2D_Create(this, w, h, rgba32Data, dataLength);
    }

    Texture2D::~Texture2D()
    {
        if (server)
            server->Texture2D_Destroy(id);
    }

    void Texture2D::Resize(const uint64_t width, const uint64_t height)
    {
        if (server)
            server->Texture2D_Resize(id, width, height);
    }

    void Texture2D::SetData(const uint32_t* const rgba32Data, const uint64_t dataLength)
    {
        if (server)
            server->Texture2D_SetData(id, rgba32Data, dataLength);
    }

    void Texture2D::SetData(const Colour& fillColour)
    {
        if (server)
            server->Texture2D_SetData(id, fillColour);
    }
}