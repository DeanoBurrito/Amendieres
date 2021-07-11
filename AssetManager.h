#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>
#include "Json/JsonParser.h"
#include "AssetBase.h"
#include "AssetHeader.h"
#include "IdManager.h"

namespace Amendieres
{
    class AssetManager
    {
    public:
        static AssetManager* The();

        void ReadConfig(const std::string& directory);
        void LoadAll();
        void UnloadAll();
        void ClearAll();
        void Load(const std::string& path);
        void Unload(const std::string& path);

        void RegisterFactory(const std::string& name, std::function<AssetBase* (uint64_t)> func);

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
        IdManager<uint64_t> idManager;
        std::map<std::string, AssetHeader*> headers;
        std::map<uint64_t, AssetBase*> assets;
        std::unique_ptr<JsonNode> configFile;

        std::map<std::string, std::function<AssetBase*(uint64_t)>> factories;

        void LoadAssetEntry(JsonNode* node, const std::string& assetDir);
    };
}