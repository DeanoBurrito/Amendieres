#pragma once

#include <memory>
#include "../AssetBase.h"
#include "Texture2D.h"

namespace Amendieres::Gfx
{
    class PngTexture2D : public AssetBase
    {
    public:
        static AssetBase* Factory(uint64_t rid);

        std::unique_ptr<Texture2D> texture;

        bool Create(char* data, uint64_t dataCount) override;
        void Destroy() override;

    private:
        PngTexture2D(uint64_t rid);
        ~PngTexture2D();
    };
}