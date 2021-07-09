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

    Texture2D* SfmlRenderServer::Texture2D_Create()
    {
        Texture2D* texture = new Texture2D(this);
        sf::Texture* sfTexture;

        textures.try_emplace(texture, SfmlBoundObj(texture, sfTexture, SfmlBoundObjType::Texture2D));

        return texture;
    }

    Texture2D* SfmlRenderServer::Texture2D_Create(const uint64_t width, const uint64_t height)
    {}

    Texture2D* SfmlRenderServer::Texture2D_Create(const uint64_t width, const uint64_t height, const uint32_t* const rgba32Data, const uint64_t dataLength)
    {}

    void SfmlRenderServer::Texture2D_Destroy(Texture2D* item)
    {}

    void SfmlRenderServer::Texture2D_Resize(Texture2D* item, const uint64_t newWidth, const uint64_t newHeight)
    {}

    void SfmlRenderServer::Texture2D_SetData(Texture2D* item, const uint32_t* const rgba32Data, const uint64_t dataLength)
    {}

    void SfmlRenderServer::Texture2D_SetData(Texture2D* item, const Colour& fillColour)
    {}


    Text2D* SfmlRenderServer::Text2D_Create()
    { return nullptr; }

    Text2D* SfmlRenderServer::Text2D_Create(const std::string& text)
    { return nullptr; }

    Text2D* SfmlRenderServer::Text2D_Create(const std::string& text, const float fontSize)
    { return nullptr; }

    void SfmlRenderServer::Text2D_Destroy(Text2D* item)
    {}

    void SfmlRenderServer::Text2D_SetText(Text2D* item, const std::string& newText)
    {}

    void SfmlRenderServer::Text2D_SetFontSize(Text2D* item, const float newSize)
    {}

    void SfmlRenderServer::Text2D_SetColor(Text2D* item, const Colour& newColor)
    {}


    RenderTexture2D* SfmlRenderServer::RenderTexture2D_Create(const uint64_t width, const uint64_t height)
    {}

    RenderTexture2D* SfmlRenderServer::RenderTexture2D_Create(const uint64_t width, const uint64_t height, const Colour& defaultColour)
    {}

    void SfmlRenderServer::RenderTexture2D_Destroy(RenderTexture2D* item)
    {}

    void SfmlRenderServer::RenderTexture2D_Clear(RenderTexture2D* item, const Colour& clearColor)
    {}

    void SfmlRenderServer::RenderTexture2D_CopyTo(const RenderTexture2D* const source, RenderTexture2D* const dest)
    {}


    void SfmlRenderServer::StartRenderQueue(const RenderQueueOptions& options)
    {}

    void SfmlRenderServer::EndRenderQueue()
    {}

    void SfmlRenderServer::Render(const Renderable2D& renderable)
    {}


    RenderTexture2D* SfmlRenderServer::RenderTexture2D_Create(void* bindingWindow)
    {}
}