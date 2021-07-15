#pragma once

#include <cstdint>
#include <string>
#include "RenderFwd.h"
#include "../Windowing/ExtWindow.h"

namespace Amendieres::Gfx
{
    class RenderServerAPI
    {
    public:
        static void SetInstance(RenderServerAPI* const inst);
        static RenderServerAPI* The();

        virtual void Init(const std::string& configName) = 0;
        virtual void Shutdown() = 0;
        virtual bool ReloadConfig(const std::string& newConfig = nullptr) = 0;

        //Texture2D stuff
        virtual uint64_t Texture2D_Create(Texture2D* const inst, const uint64_t width, const uint64_t height) = 0;
        virtual uint64_t Texture2D_Create(Texture2D* const inst, const uint64_t width, const uint64_t height, const uint32_t* const rgba32Data, const uint64_t dataLength) = 0;
        virtual void Texture2D_Destroy(const uint64_t itemId) = 0;
        virtual void Texture2D_Resize(const uint64_t itemid, const uint64_t newWidth, const uint64_t newHeight) = 0;
        virtual void Texture2D_SetData(const uint64_t itemId, const uint32_t* const rgba32Data, const uint64_t dataLength) = 0;
        virtual void Texture2D_SetData(const uint64_t itemId, const Colour& fillColour) = 0;

        //DynamicFont stuff
        virtual uint64_t DynamicFont_Create(DynamicFont* const inst, const uint8_t* const fontFileData, const uint64_t dataLength) = 0;
        virtual uint64_t DynamicFont_Create(DynamicFont* const inst, const uint8_t* const fontFileData, const uint64_t dataLength, const uint8_t renderSize) = 0;
        virtual void DynamicFont_Destroy(uint64_t itemId) = 0;
        virtual void DynamicFont_RasterForSize(uint64_t itemId) = 0;
        virtual FontGlyph* DynamicFont_GetGlyph(uint64_t itemId, int character) = 0;

        //Text2D stuff
        virtual uint64_t Text2D_Create() = 0;
        virtual uint64_t Text2D_Create(const std::string& text) = 0;
        virtual uint64_t Text2D_Create(const std::string& text, const uint8_t fontSize) = 0;
        virtual void Text2D_Destroy(const uint64_t itemId) = 0;
        virtual void Text2D_SetText(const uint64_t itemId, const std::string& newText) = 0;
        virtual void Text2D_SetFontSize(const uint64_t itemId, const float newSize) = 0;
        virtual void Text2D_SetColor(const uint64_t itemId, const Colour& newColor) = 0;

        //RenderTexture2D stuff
        virtual uint64_t RenderTexture2D_Create(RenderTexture2D* const inst, const uint64_t width, const uint64_t height) = 0;
        virtual uint64_t RenderTexture2D_Create(RenderTexture2D* const inst, const uint64_t width, const uint64_t height, const Colour& defaultColour) = 0;
        virtual uint64_t RenderTexture2D_Create(RenderTexture2D* const inst, Windowing::ExtWindow* bindingWindow) = 0;
        virtual void RenderTexture2D_Destroy(const uint64_t itemId) = 0;
        virtual void RenderTexture2D_Clear(const uint64_t itemId, const Colour& clearColor) = 0;
        virtual void RenderTexture2D_CopyTo(const uint64_t sourceId, uint64_t destId) = 0;

        //Render queue and render commands
        virtual void StartRenderQueue(const RenderQueueOptions& options) = 0;
        virtual void EndRenderQueue() = 0;
        virtual void Render(const Renderable2D& renderable) = 0;
    };
}