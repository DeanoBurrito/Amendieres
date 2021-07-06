#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>
#include "JsonParser.h"
#include "AssetBase.h"
#include "AssetHeader.h"

namespace Amendieres
{
    class AssetManager
    {
    public:
        static AssetManager* The();

        void ReadConfig(const std::string& directory);
        void LoadAll();
        void Load(const std::string& path);
        void Unload(const std::string& path);

        void RegisterFactory(const std::string& name, std::function<AssetBase* (uint64_t)>);

        AssetHeader* GetHeader(const std::string& path) const;
        AssetBase* Get(const std::string& path); 

        template <class T>
        T* Get(const std::string& path)
        {
            static_assert(std::is_base_of<AssetBase, T>(), "Cannot get resource that dosnt implement AssetBase.");

            AssetBase* base = Get(path);
            if (base != nullptr)
                return static_cast<T*>(base);
            return nullptr;
        }
    private:
        std::map<std::string, AssetHeader*> headers;
        std::map<uint64_t, AssetBase*> assets;
        std::unique_ptr<JsonNode> configFile;

        void LoadAssetEntry(JsonNode* node);
    };
}