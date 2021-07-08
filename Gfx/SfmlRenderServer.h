#pragma once

#include "RenderServerAPI.h"

namespace Amendieres::Gfx
{
    class SfmlRenderServer : public RenderServerAPI
    {
    public:
        void Init(const std::string &configName) override;
        void Shutdown() override;
        bool ReloadConfig(const std::string &newConfig = nullptr) override;

        Texture2D* Texture2D_Create() override;
        Texture2D* Texture2D_Create(const uint64_t width, const uint64_t height) override;
        Texture2D* Texture2D_Create(const uint64_t width, const uint64_t height, const uint32_t* const rgba32Data, const uint64_t dataLength) override;
        void Texture2D_Destroy(Texture2D* item) override;
        void Texture2D_Resize(Texture2D* item, const uint64_t newWidth, const uint64_t newHeight) override;
        void Texture2D_SetData(Texture2D* item, const uint32_t* const rgba32Data, const uint64_t dataLength) override;
        void Texture2D_SetData(Texture2D* item, const Colour& fillColour) override;

        Text2D* Text2D_Create() override;
        Text2D* Text2D_Create(const std::string& text) override;
        Text2D* Text2D_Create(const std::string& text, const float fontSize) override;
        void Text2D_Destroy(Text2D* item) override;
        void Text2D_SetText(Text2D* item, const std::string& newText) override;
        void Text2D_SetFontSize(Text2D* item, const float newSize) override;
        void Text2D_SetColor(Text2D* item, const Colour& newColor) override;

        RenderTexture2D* RenderTexture2D_Create(const uint64_t width, const uint64_t height) override;
        RenderTexture2D* RenderTexture2D_Create(const uint64_t width, const uint64_t height, const Colour& defaultColour) override;
        void RenderTexture2D_Destroy(RenderTexture2D* item) override;
        void RenderTexture2D_Clear(RenderTexture2D* item, const Colour& clearColor) override;
        void RenderTexture2D_CopyTo(const RenderTexture2D* const source, RenderTexture2D* const dest) override;

        void StartRenderQueue(const RenderQueueOptions& options) override;
        void EndRenderQueue() override;
        void Render(const Renderable2D& renderable) override;
    
    protected:
        RenderTexture2D* RenderTexture2D_Create(void* bindingWindow) override;
    }; 
}