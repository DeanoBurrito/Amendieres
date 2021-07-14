#include "../Debug.h"
#include "RenderTexture2D.h"

namespace Amendieres::Gfx
{
    RenderTexture2D::RenderTexture2D(RenderServerAPI* const api, const uint64_t width, const uint64_t height)
    {
        DEBUG_RETURN_IF(api == nullptr, "Cannot create RenderTexture2D with nullptr for api!");

        server = api;
        id = server->RenderTexture2D_Create(this, width, height);
    }

    RenderTexture2D::RenderTexture2D(RenderServerAPI* const api, const uint64_t width, const uint64_t height, const Colour& defaultFill)
    {
        DEBUG_RETURN_IF(api == nullptr, "Cannot create RenderTexture2D with nullptr for api!");

        server = api;
        id = server->RenderTexture2D_Create(this, width, height, defaultFill);
    }

    RenderTexture2D::RenderTexture2D(RenderServerAPI* const api, Windowing::ExtWindow* bindingWindow)
    {
        DEBUG_RETURN_IF(api == nullptr, "Cannot create RenderTexture2D with nullptr for api!");

        server = api;
        id = server->RenderTexture2D_Create(this, bindingWindow);
    }

    RenderTexture2D::~RenderTexture2D()
    {
        if (server)
            server->RenderTexture2D_Destroy(id);
    }

    void RenderTexture2D::Clear(const Colour& colour)
    {
        DEBUG_RETURN_IF(server == nullptr, LOG_WHERE << "Cannot clear RenderTexture2D, server is nullptr");

        server->RenderTexture2D_Clear(id, colour);
    }

    void RenderTexture2D::CopyTo(RenderTexture2D* const destination)
    {
        DEBUG_RETURN_IF(destination == nullptr, LOG_WHERE << "Cannot copy RenderTexture2D, target is nullptr.");
        DEBUG_RETURN_IF(server == nullptr, LOG_WHERE << "Cannot copy RenderTexture2D, server is nullptr.");

        server->RenderTexture2D_CopyTo(id, destination->id);
    }
}