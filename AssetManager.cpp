#include "AssetManager.h"

namespace Amendieres
{
    AssetManager* AssetManager::The()
    {
        static AssetManager* instance = nullptr;
        if (instance == nullptr)
            instance = new AssetManager();
        return instance;
    }

    void AssetManager::ReadConfig(const std::string& directory)
    {
        JsonParser parser;
        configFile = parser.ParseFile(directory + "/assets.json");
    }

    void AssetManager::LoadAll()
    {

    }

    void AssetManager::Load(const std::string& path)
    {}

    void AssetManager::Unload(const std::string& path)
    {}

    void AssetManager::RegisterFactory(const std::string& name, std::function<AssetBase* (uint64_t)>)
    {}

    AssetHeader* AssetManager::GetHeader(const std::string& path) const
    { return nullptr; }

    AssetBase* AssetManager::Get(const std::string& path)
    { return nullptr; }

    void AssetManager::LoadAssetEntry(JsonNode* node)
    {

    }
}