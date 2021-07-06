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

        std::string fileLocation;
        uint64_t fileOffset;
        uint64_t fileLength;
    
        AssetHeader(const std::string& assetName, const std::string& loaderName, const std::string& filename) : name(assetName)
        {
            loaded = false;
            loadedId = 0;
            loaderFunction = loaderName;
            fileLocation = filename;
            fileOffset = 0;
            fileLength = 0;
        }
    private:
        uint64_t loadedId;
    };
}