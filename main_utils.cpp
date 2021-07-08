#include "AssetManager.h"
#include "Json/JsonAsset.h"

namespace Amendieres
{
    void RegisterAssetFactories()
    {
        AssetManager::The()->RegisterFactory("JSON", JsonAsset::Factory);
    }
}