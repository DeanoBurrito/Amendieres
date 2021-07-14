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

    uint64_t SfmlRenderServer::Texture2D_Create(Texture2D* const inst, const uint64_t width, const uint64_t height)
    { 
        sf::Texture* sfTexture = new sf::Texture();
        if (!sfTexture->create(width, height))
        {
            LOG_ERROR("SFML render server failed to create texture: w=" << width << ", h=" << height);
            return 0;
        }

        uint64_t localId = idManager.AllocId();
        textures.try_emplace(localId, SfmlBoundObj(inst, sfTexture, SfmlBoundObjType::Texture2D));

        return localId;
    }

    uint64_t SfmlRenderServer::Texture2D_Create(Texture2D* const inst, const uint64_t width, const uint64_t height, const uint32_t* const rgba32Data, const uint64_t dataLength)
    { 
        uint64_t setId = Texture2D_Create(inst, width, height);
        if (setId == 0)
            return 0;
        
        sf::Texture* sfTexture = static_cast<sf::Texture*>(textures.find(setId)->second.sfObj);
        //pretty shocking, but at the end of the day sfml *shouldnt* be changing the pointer value.
        const uint8_t* sfmlFriendlyPtr = static_cast<const uint8_t*>((const void*)rgba32Data);
        sfTexture->update(sfmlFriendlyPtr); //sfml just assumes the data length matches.

        return setId;
    }

    void SfmlRenderServer::Texture2D_Destroy(const uint64_t itemId)
    {
        auto boundObj = textures.find(itemId);
        if (boundObj == textures.end())
        {
            LOG_ERROR("SFML could not destroy texture2d: texture does not belong to this render server. id=" << itemId);
            return;
        }

        sf::Texture* sfTex = static_cast<sf::Texture*>(boundObj->second.sfObj);
        textures.erase(itemId);
        
        delete sfTex;
        idManager.FreeId(itemId);
    }

    void SfmlRenderServer::Texture2D_Resize(const uint64_t itemId, const uint64_t newWidth, const uint64_t newHeight)
    {}

    void SfmlRenderServer::Texture2D_SetData(const uint64_t itemId, const uint32_t* const rgba32Data, const uint64_t dataLength)
    {
        auto boundObj = textures.find(itemId);
        if (boundObj == textures.end())
        {
            LOG_ERROR("Unable to set Texture2D data, not owned by this render server. Id=" << itemId);
            return;
        }

        sf::Texture* sfTex = static_cast<sf::Texture*>(boundObj->second.sfObj);
        const uint8_t* sfmlFriendlyPtr = static_cast<const uint8_t*>((const void*)rgba32Data);
        sfTex->update(sfmlFriendlyPtr);
    }

    void SfmlRenderServer::Texture2D_SetData(const uint64_t itemId, const Colour& fillColour)
    {
        auto boundObj = textures.find(itemId);
        if (boundObj == textures.end())
        {
            LOG_ERROR("Unable to set Texture2D data, not owned by this render server. Id=" << itemId);
            return;
        }

        sf::Texture* sfTex = static_cast<sf::Texture*>(boundObj->second.sfObj);
        sf::Image image;
        image.create(sfTex->getSize().x, sfTex->getSize().y, sf::Color(fillColour.GetPacked()));
        sfTex->update(image);
    }


    uint64_t SfmlRenderServer::Text2D_Create()
    { return 0; }

    uint64_t SfmlRenderServer::Text2D_Create(const std::string& text)
    { return 0; }

    uint64_t SfmlRenderServer::Text2D_Create(const std::string& text, const uint8_t fontSize)
    { return 0; }

    void SfmlRenderServer::Text2D_Destroy(const uint64_t itemId)
    {}

    void SfmlRenderServer::Text2D_SetText(const uint64_t itemId, const std::string& newText)
    {}

    void SfmlRenderServer::Text2D_SetFontSize(const uint64_t itemId, const float newSize)
    {}

    void SfmlRenderServer::Text2D_SetColor(const uint64_t itemId, const Colour& newColor)
    {}


    uint64_t SfmlRenderServer::RenderTexture2D_Create(RenderTexture2D* const inst, const uint64_t width, const uint64_t height)
    { 
        sf::RenderTexture* sfRenderTexture = new sf::RenderTexture();
        if (!sfRenderTexture->create(width, height))
        {
            LOG_ERROR("Unable to create RenderTexture2D, SFML failed to initialize rendertarget.");
            return 0;
        }

        uint64_t localId = idManager.AllocId();
        renderTextures.try_emplace(localId, SfmlBoundObj(inst, sfRenderTexture, SfmlBoundObjType::RenderTexture2D));

        return localId;
    }

    uint64_t SfmlRenderServer::RenderTexture2D_Create(RenderTexture2D* const inst, const uint64_t width, const uint64_t height, const Colour& defaultColour)
    { 
        uint64_t localId = RenderTexture2D_Create(inst, width, height);
        if (localId == 0)
            return localId;

        sf::RenderTexture* sfRenderTexture = static_cast<sf::RenderTexture*>(renderTextures.find(localId)->second.sfObj);
        const uint32_t packedColour = defaultColour.GetPacked(ColourPackingOrder::RGBA);
        sfRenderTexture->clear(sf::Color(packedColour));

        return localId;
    }

    uint64_t SfmlRenderServer::RenderTexture2D_Create(RenderTexture2D* const inst, Windowing::ExtWindow* bindingWindow)
    { 
        if (Windowing::WindowServerAPI::The()->GetImplName().compare("SfmlWindowServer") == 0)
        {
            //SFML window server implementation
            void* implHandle = Windowing::WindowServerAPI::The()->GetImplSpecificHandle(bindingWindow);
            if (implHandle == nullptr)
            {
                LOG_ERROR("Something has gone horribly wrong: Cannot create RenderTexture2D from ExtWindow, window server returned nullptr as a handle!");
                return 0;
            }

            sf::RenderWindow* sfWindow = static_cast<sf::RenderWindow*>(implHandle);
            uint64_t localId = idManager.AllocId();
            renderTextures.try_emplace(localId, SfmlBoundObj(inst, sfWindow, SfmlBoundObjType::RenderTexture2D_Window));

            return localId;
        }
        else
        {
            LOG_ERROR("Unknown window server implementation, cannot bind window to rendertexture!");
            return 0;
        }
    }

    void SfmlRenderServer::RenderTexture2D_Destroy(const uint64_t itemId)
    {
        auto boundObj = renderTextures.find(itemId);
        if (boundObj == renderTextures.end())
        {
            LOG_ERROR("Unable to destroy RenderTexture2D, id does not exist for this server.");
            return;
        }

        if (boundObj->second.type == SfmlBoundObjType::RenderTexture2D)
        {
            sf::RenderTexture* sfRenderTexture = static_cast<sf::RenderTexture*>(boundObj->second.sfObj);
            delete sfRenderTexture;
        }
        /*
            Ignoring sf::RenderWindow pointer here, this is not a resource leak. The window server is responsible for any window pointers,
            and thus freeing it here would likely result in multiple attempts to free it.
        */

        renderTextures.erase(itemId);
        idManager.FreeId(itemId);
    }

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
}