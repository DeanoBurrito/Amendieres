#pragma once

#include <string>
#include "AssetBase.h"

namespace Amendieres
{
    class AssetManager;
    
    class AssetHeader
    {
    friend AssetManager;
    public:
        const std::string name;
        bool loaded;
        std::string loaderFunction;
    
        AssetHeader(const std::string& assetName, const std::string& loaderName) : name(assetName)
        {
            loaded = false;
            loaderFunction = loaderName;
        }
    private:
        uint64_t loadedId;
    };
}