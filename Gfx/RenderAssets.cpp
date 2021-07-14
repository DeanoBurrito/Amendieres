#include "stb_image.h"
#include "../Debug.h"
#include "RenderAssets.h"

namespace Amendieres::Gfx
{
    AssetBase* PngTexture2D::Factory(uint64_t rid)
    {
        return new PngTexture2D(rid);
    }

    PngTexture2D::PngTexture2D(uint64_t rid) : AssetBase(rid, static_cast<int32_t>(AssetType::PngTexture))
    {}

    PngTexture2D::~PngTexture2D()
    {}

    bool PngTexture2D::Create(char* data, uint64_t dataCount)
    {
        int width;
        int height;
        int actualChannels;
        int desiredChannels = STBI_rgb_alpha;
        unsigned char* parsedData = stbi_load_from_memory(reinterpret_cast<unsigned char*>(data), dataCount, &width, &height, &actualChannels, desiredChannels);

        Texture2D* texPtr = new Texture2D(width, height, reinterpret_cast<uint32_t*>(parsedData), width * height);
        if (!texPtr->IsValid())
        {
            delete texPtr;
            return false;
        }

        texture = std::unique_ptr<Texture2D>(texPtr);
        return true;
    }

    void PngTexture2D::Destroy()
    {
        texture.reset();
    }
}