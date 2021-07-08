#pragma once

#include <cstdint>
#include <string>

namespace Amendieres::Gfx
{
    class Renderable2D; //base 2d drawable class
    class Texture2D;
    class RenderTexture2D;
    class Text2D;
    class Colour;
    class RenderQueueOptions; //includes target to output to, shaders to use
    
    class RenderServerAPI
    {
    public:
        virtual void Init(const std::string& configName) = 0;
        virtual void Shutdown() = 0;
        virtual bool ReloadConfig(const std::string& newConfig = nullptr) = 0;

        //Texture2D stuff
        virtual Texture2D* Texture2D_Create() = 0;
        virtual Texture2D* Texture2D_Create(const uint64_t width, const uint64_t height) = 0;
        virtual Texture2D* Texture2D_Create(const uint64_t width, const uint64_t height, const uint32_t* const rgba32Data, const uint64_t dataLength) = 0;
        virtual void Texture2D_Destroy(Texture2D* item) = 0;
        virtual void Texture2D_Resize(const uint64_t newWidth, const uint64_t newHeight) = 0;
        virtual void Texture2D_SetData(Texture2D* item, const uint32_t* const rgba32Data, const uint64_t dataLength) = 0;
        virtual void Texture2D_SetData(Texture2D* item, const Colour& fillColour) = 0;

        //Text2D stuff
        virtual Text2D* Text2D_Create() = 0;
        virtual Text2D* Text2D_Create(const std::string& text) = 0;
        virtual Text2D* Text2D_Create(const std::string& text, const float fontSize) = 0;
        virtual void Text2D_Destroy(Text2D* item) = 0;
        virtual void Text2D_SetText(Text2D* item, const std::string& newText) = 0;
        virtual void Text2D_SetFontSize(Text2D* item, const float newSize) = 0;
        virtual void Text2D_SetColor(Text2D* item, const Colour& newColor) = 0;

        //RenderTexture2D stuff
        virtual RenderTexture2D* RenderTexture2D_Create(const uint64_t width, const uint64_t height) = 0;
        virtual RenderTexture2D* RenderTexture2D_Create(const uint64_t width, const uint64_t height, const Colour& defaultColour) = 0;
        virtual void RenderTexture2D_Destroy(RenderTexture2D* item) = 0;
        virtual void RenderTexture2D_Clear(const Colour& clearColor) = 0;
        virtual void RenderTexture2D_CopyTo(const RenderTexture2D* const source, RenderTexture2D* const dest) = 0;

        //Render queue and render commands
        virtual void StartRenderQueue(const RenderQueueOptions& options) = 0;
        virtual void EndRenderQueue() = 0;
        virtual void Render(const Renderable2D& renderable) = 0;

    protected:
        virtual RenderTexture2D* RenderTexture2D_Create(void* bindingWindow) = 0;
    };
}