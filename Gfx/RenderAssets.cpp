#include "stb_image.h"
#include "../Debug.h"
#include "RenderAssets.h"

namespace Amendieres::Gfx
{
    AssetBase* PngTexture2D::Factory(const uint64_t rid)
    {
        return new PngTexture2D(rid);
    }

    PngTexture2D::PngTexture2D(const uint64_t rid) : AssetBase(rid, static_cast<int32_t>(AssetType::PngTexture))
    {}

    bool PngTexture2D::Create(char* data, uint64_t dataCount)
    {
        int width;
        int height;
        int actualChannels;
        int desiredChannels = STBI_rgb_alpha;
        unsigned char* parsedData = stbi_load_from_memory(reinterpret_cast<unsigned char*>(data), dataCount, &width, &height, &actualChannels, desiredChannels);

        if (parsedData == NULL)
        {
            LOG_ERROR("Could not load PNG image: " << stbi_failure_reason());
            return false;
        }

        Texture2D* texPtr = new Texture2D(width, height, reinterpret_cast<uint32_t*>(parsedData), width * height);
        if (!texPtr->IsValid())
        {
            LOG_ERROR("Could not created Texture2D from PNG image: " << stbi_failure_reason());

            stbi_image_free(parsedData);
            delete texPtr;
            return false;
        }

        stbi_image_free(parsedData);
        texture = std::unique_ptr<Texture2D>(texPtr);
        return true;
    }

    void PngTexture2D::Destroy()
    {
        texture.reset();
    }

    AssetBase* TrueTypeDynamicFont::Factory(const uint64_t rid)
    {
        return new TrueTypeDynamicFont(rid);
    }

    TrueTypeDynamicFont::TrueTypeDynamicFont(const uint64_t rid) : AssetBase(rid, static_cast<int32_t>(AssetType::TrueTypeFont))
    {}

    bool TrueTypeDynamicFont::Create(char *data, uint64_t dataCount)
    {
        DynamicFont* fontPtr = new DynamicFont(data, dataCount);
        font = std::unique_ptr<DynamicFont>(fontPtr);
        //TODO: should be checking if fontPtr is valid. Move id to base renderable class, and IsValid() can be moved there.

        return true;
    }

    void TrueTypeDynamicFont::Destroy()
    {
        font.reset();
    }
}