#pragma once

#include <unordered_map>
#include "RenderServerAPI.h"
#include "SfmlBoundObj.h"
#include "../IdManager.h"
#include "ft2build.h"
#include FT_FREETYPE_H

namespace Amendieres::Gfx
{   
    class SfmlRenderServer : public RenderServerAPI
    {
    public:
        void Init(const std::string& configName) override;
        void Shutdown() override;
        bool ReloadConfig(const std::string& newConfig = nullptr) override;

        uint64_t Texture2D_Create(Texture2D* const inst, const uint64_t width, const uint64_t height) override;
        uint64_t Texture2D_Create(Texture2D* const inst, const uint64_t width, const uint64_t height, const uint32_t* const rgba32Data, const uint64_t dataLength) override;
        void Texture2D_Destroy(const uint64_t itemId) override;
        void Texture2D_Resize(const uint64_t itemId, const uint64_t newWidth, const uint64_t newHeight) override;
        void Texture2D_SetData(const uint64_t itemId, const uint32_t* const rgba32Data, const uint64_t dataLength) override;
        void Texture2D_SetData(const uint64_t itemId, const Colour& fillColour) override;

        uint64_t DynamicFont_Create(DynamicFont* const inst, const char* const fontFileData, const uint64_t dataLength) override;
        uint64_t DynamicFont_Create(DynamicFont* const inst, const char* const fontFileData, const uint64_t dataLength, const uint8_t renderSize) override;
        void DynamicFont_Destroy(uint64_t itemId) override;

        uint64_t Text2D_Create() override;
        uint64_t Text2D_Create(const std::string& text) override;
        uint64_t Text2D_Create(const std::string& text, const uint8_t fontSize) override;
        void Text2D_Destroy(const uint64_t itemId) override;
        void Text2D_SetText(const uint64_t itemId, const std::string& newText) override;
        void Text2D_SetFontSize(uint64_t, const float newSize) override;
        void Text2D_SetColor(uint64_t, const Colour& newColor) override;

        uint64_t RenderTexture2D_Create(RenderTexture2D* const inst, const uint64_t width, const uint64_t height) override;
        uint64_t RenderTexture2D_Create(RenderTexture2D* const inst, const uint64_t width, const uint64_t height, const Colour& defaultColour) override;
        uint64_t RenderTexture2D_Create(RenderTexture2D* const inst, Windowing::ExtWindow* bindingWindow) override;
        void RenderTexture2D_Destroy(const uint64_t itemId) override;
        void RenderTexture2D_Clear(const uint64_t itemId, const Colour& clearColor) override;
        void RenderTexture2D_CopyTo(const uint64_t sourceId, const uint64_t destId) override;

        void StartRenderQueue(const RenderQueueOptions& options) override;
        void EndRenderQueue() override;
        void Render(const Renderable2D& renderable) override;
        
    private:
        std::unordered_map<uint64_t, SfmlBoundObj> textures;
        std::unordered_map<uint64_t, SfmlBoundObj> renderTextures;
        std::unordered_map<uint64_t, SfmlBoundObj> dynamicFonts;
        
        IdManager<uint64_t> idManager;
        FT_Library freetypeLibrary;
    }; 
}