#include "AssetManager.h"
#include "JsonAsset.h"

namespace Amendieres
{
    void RegisterAssetFactories()
    {
        AssetManager::The()->RegisterFactory("JSON", JsonAsset::Factory);
    }
}