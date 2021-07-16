#pragma once

#include <memory>
#include "../AssetBase.h"
#include "Texture2D.h"
#include "DynamicFont.h"

namespace Amendieres::Gfx
{
    class PngTexture2D : public AssetBase
    {
    public:
        static AssetBase* Factory(const uint64_t rid);

        std::unique_ptr<Texture2D> texture;

        bool Create(char* data, uint64_t dataCount) override;
        void Destroy() override;

    private:
        PngTexture2D(const uint64_t rid);
    };

    class TrueTypeDynamicFont : public AssetBase
    {
    public:
        static AssetBase* Factory(const uint64_t rid);

        std::unique_ptr<DynamicFont> font;

        bool Create(char* data, uint64_t dataCount) override;
        void Destroy() override;

    private:
        TrueTypeDynamicFont(const uint64_t rid);
    };
}