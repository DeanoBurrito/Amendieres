#pragma once

namespace Amendieres::Gfx
{
    enum class SfmlBoundObjType
    {
        Window,
        Texture2D,
        RenderTexture2D,
        RenderTexture2D_Window,
    };

    class SfmlBoundObj
    {
    public:
        const SfmlBoundObjType type;
        void* const localObj = nullptr;
        void* const sfObj = nullptr;

        SfmlBoundObj() = delete;
        SfmlBoundObj(void* const local, void* const sfml, SfmlBoundObjType linkType)
        : type(linkType), localObj(local), sfObj(sfml)
        {}
    };
}