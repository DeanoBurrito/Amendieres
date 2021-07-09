#pragma once

namespace Amendieres::Gfx
{
    enum class SfmlBoundObjType
    {
        Window
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