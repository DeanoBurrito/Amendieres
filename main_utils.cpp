#include "AssetManager.h"
#include "Json/JsonAsset.h"
#include "Gfx/RenderAssets.h"

namespace Amendieres
{
    void RegisterAssetFactories()
    {
        AssetManager::The()->RegisterFactory("JSON", JsonAsset::Factory);
        AssetManager::The()->RegisterFactory("PNG", Gfx::PngTexture2D::Factory);
    }
}