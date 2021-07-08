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
        const std::string loaderFunction;
        const std::string fileLocation;
    
        AssetHeader(const std::string& assetName, const std::string& loaderName, const std::string& filename) 
            : name(assetName), loaderFunction(loaderName), fileLocation(filename)
        {
            loaded = false;
            loadedId = 0;
            fileOffset = 0;
            fileLength = 0;
        }

        bool IsLoaded()
        {
            return loaded;
        }
    private:
        uint64_t loadedId;
        bool loaded;

        uint64_t fileOffset;
        uint64_t fileLength;
    };
}