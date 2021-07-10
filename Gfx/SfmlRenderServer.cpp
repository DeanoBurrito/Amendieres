#include <SFML/Graphics.hpp>
#include "../Debug.h"
#include "Texture2D.h"
#include "RenderTexture2D.h"
#include "SfmlRenderServer.h"

namespace Amendieres::Gfx
{
    void SfmlRenderServer::Init(const std::string& configName)
    {
        LOG("SFML render server init(), marking as global instance.");
        SetInstance(this);
    }

    void SfmlRenderServer::Shutdown()
    {
        LOG("SFML render server shutting down.");
    }

    bool SfmlRenderServer::ReloadConfig(const std::string& newConfig)
    { return true; }

    uint64_t SfmlRenderServer::Texture2D_Create()
    {
        LOG_ERROR("SFML render server does not support creating textures without width and height being known at create().");
        return 0;
    }

    uint64_t SfmlRenderServer::Texture2D_Create(const uint64_t width, const uint64_t height)
    { return 0; }

    uint64_t SfmlRenderServer::Texture2D_Create(const uint64_t width, const uint64_t height, const uint32_t* const rgba32Data, const uint64_t dataLength)
    { return 0; }

    void SfmlRenderServer::Texture2D_Destroy(const uint64_t itemId)
    {}

    void SfmlRenderServer::Texture2D_Resize(const uint64_t itemId, const uint64_t newWidth, const uint64_t newHeight)
    {}

    void SfmlRenderServer::Texture2D_SetData(const uint64_t itemId, const uint32_t* const rgba32Data, const uint64_t dataLength)
    {}

    void SfmlRenderServer::Texture2D_SetData(const uint64_t itemId, const Colour& fillColour)
    {}


    uint64_t SfmlRenderServer::Text2D_Create()
    { return 0; }

    uint64_t SfmlRenderServer::Text2D_Create(const std::string& text)
    { return 0; }

    uint64_t SfmlRenderServer::Text2D_Create(const std::string& text, const float fontSize)
    { return 0; }

    void SfmlRenderServer::Text2D_Destroy(const uint64_t itemId)
    {}

    void SfmlRenderServer::Text2D_SetText(const uint64_t itemId, const std::string& newText)
    {}

    void SfmlRenderServer::Text2D_SetFontSize(const uint64_t itemId, const float newSize)
    {}

    void SfmlRenderServer::Text2D_SetColor(const uint64_t itemId, const Colour& newColor)
    {}


    uint64_t SfmlRenderServer::RenderTexture2D_Create(const uint64_t width, const uint64_t height)
    { return 0; }

    uint64_t SfmlRenderServer::RenderTexture2D_Create(const uint64_t width, const uint64_t height, const Colour& defaultColour)
    { return 0; }

    void SfmlRenderServer::RenderTexture2D_Destroy(const uint64_t itemId)
    {}

    void SfmlRenderServer::RenderTexture2D_Clear(const uint64_t itemId, const Colour& clearColor)
    {}

    void SfmlRenderServer::RenderTexture2D_CopyTo(const uint64_t sourceId, const uint64_t destId)
    {}


    void SfmlRenderServer::StartRenderQueue(const RenderQueueOptions& options)
    {}

    void SfmlRenderServer::EndRenderQueue()
    {}

    void SfmlRenderServer::Render(const Renderable2D& renderable)
    {}


    uint64_t SfmlRenderServer::RenderTexture2D_Create(void* bindingWindow)
    { return 0; }
}