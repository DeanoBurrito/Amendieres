#pragma once

namespace Amendieres::Gfx
{
    enum class RenderBoundObjType
    {
        Window,
        Texture2D,
        RenderTexture2D,
        RenderTexture2D_Window,
        FontFace,
    };

    class RenderBoundObj
    {
    public:
        const RenderBoundObjType type;
        void* const localObj = nullptr;
        void* const sfObj = nullptr;

        RenderBoundObj() = delete;
        RenderBoundObj(void* const local, void* const sfml, RenderBoundObjType linkType)
        : type(linkType), localObj(local), sfObj(sfml)
        {}

        RenderBoundObj(const RenderBoundObj &) = delete;
        void operator=(const RenderBoundObj &) = delete;
        RenderBoundObj(RenderBoundObj&&) = delete;
    };
}