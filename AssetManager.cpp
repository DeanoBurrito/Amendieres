#include <iostream>
#include <fstream>
#include <cassert>
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
        if (assets[0] == nullptr)
        {
            //create empty asset
            assets[0] = new EmptyAsset();
        }
    }

    void AssetManager::UnloadAll()
    {
        for (auto& header : headers)
        {
            if (header.second->loaded)
                Unload(header.first);
        }
        assert(assets.size() == 0);
    }

    void AssetManager::ClearAll()
    {
        UnloadAll();
        for (auto& asset : headers)
        {
            delete asset.second;
        }
        headers.clear();
        assert(freedRids.size() == nextRid - 1);
    }

    void AssetManager::Load(const std::string& path)
    {
        //lookup header, abort op if it dosnt exist
        auto header = headers.find(path);
        if (header == headers.end())
        {
            std::cerr << "Unable to load resource with path: " << path << std::endl;
            return;
        }

        if (header->second->loaded)
            return;

        //lookup creator function for specific resource type, keep it typesafe from the get go.        
        auto factory = factories.find(header->second->loaderFunction);
        if (factory == factories.end())
        {
            std::cerr << "Unable to load resource, no loader registered for type: " << header->second->loaderFunction << std::endl;
            return;
        }

        //validate file actually exists, and offset + length arent going to trigger any weirdness
        std::ifstream inFile(header->second->fileLocation, std::ios::in);
        if (!inFile.is_open())
        {
            std::cerr << "Unable to load resource" << path << ", referenced file does not exist: " << header->second->fileLocation << std::endl;
            //inFile.close(); //this shouldnt do anything, i've left it as a reminder for future me to verify across multiple OS's.
            return;
        }
        inFile.seekg(0, std::ios::end);

        uint64_t fileLength = inFile.tellg();
        if (fileLength < header->second->fileOffset + header->second->fileLength)
        {
            std::cerr << "Unable to load resource " << path << ", file does not have enough data." << std::endl;
            inFile.close();
            return;
        }
        inFile.seekg(header->second->fileOffset); //seek to offset prior to passing stream to Create()

        //create asset with unique id, cache it and create it using file from earlier
        AssetBase* base = factory->second(AllocId());
        #warning Assets are being passed a LIVE file stream when being loaded. Ideally this is an isolated pre-read copy in memory.
        if (!base->Create(inFile))
        {
            std::cerr << "Unable to load resource, Create() failed. " << path << std::endl;
            
            delete base;
            FreeId(base->id);
            return;
        }
        assets[base->id] = base;

        //cleanup and linking header with instance
        inFile.close();
        header->second->loaded = true;
        header->second->loadedId = base->id;
    }

    void AssetManager::Unload(const std::string& path)
    {
        //lookup header and validate it's loaded in the first place
        auto header = headers.find(path);
        if (header == headers.end())
        {
            std::cerr << "Unable to unload resource with path: " << path << std::endl;
            return;
        }

        if (!header->second->loaded)
            return;
        
        //getting instance ptr
        if (assets.find(header->second->loadedId) != assets.end())
        {
            std::cerr << "Unable to unload resource " << path << ", could not find resource instance" << std::endl;
            header->second->loaded = false;
            header->second->loadedId = 0;
            return;
        }

        //destroy resource and clean up links
        AssetBase* base = assets.find(header->second->loadedId)->second;
        header->second->loaded = false;
        header->second->loadedId = 0;

        assets.erase(base->id);
        FreeId(base->id);
        base->Destroy();
        delete base;
    }

    void AssetManager::RegisterFactory(const std::string& name, std::function<AssetBase* (uint64_t)> func)
    {
        if (factories.find(name) != factories.end())
        {
            std::cout << "Skipping factory " << name << ", a function is already registered to that type." << std::endl;
            return;
        }

        factories[name] = func;
    }

    AssetHeader* AssetManager::GetHeader(const std::string& path) const
    { return nullptr; }

    AssetBase* AssetManager::Get(const std::string& path)
    { return nullptr; }

    void AssetManager::LoadAssetEntry(JsonNode* node)
    {
        std::string name;
        std::string fileName;
        std::string loaderName;
        bool essentialFilled = true;
        //lots of dangling ptrs, these are just references inside the tree, and will be cleaned up with the tree itself
        if (JsonString* nameNode = node->Find<JsonString>("name"))
            name = nameNode->value;
        if (JsonString* filenameNode = node->Find<JsonString>("file/name"))
        {
            fileName = filenameNode->value;
            if (name.size() == 0)
                fileName = fileName;
        }
        else
            essentialFilled = false;
            
        if (JsonString* loaderNode = node->Find<JsonString>("loader"))
            loaderName = loaderNode->value;
        else
            essentialFilled = false;
        
        //before we allocate, check if name is valid
        if (headers.find(name) != headers.end())
        {
            std::cerr << "Failed loading asset header entry: Header already exists for entry " << name << std::endl;
            return;
        }

        
        //create entry if we have the essentials
        if (!essentialFilled)
        {
            std::cerr << "Failed loading asset header entry: Required details missing from config file. Possibly resource " << fileName << std::endl;
            return;
        }

        //optional values
        AssetHeader* header = new AssetHeader(name, loaderName, fileName);
        if (JsonNumberInt* fileStart = node->Find<JsonNumberInt>("file/offset"))
            header->fileOffset = fileStart->value;
        if (JsonNumberInt* fileLength = node->Find<JsonNumberInt>("file/length"))
            header->fileLength = fileLength->value;
        
        //finally add it to the stash
        headers[name] = header;
    }

    uint64_t AssetManager::AllocId()
    {
        uint64_t retId;
        
        if (freedRids.size() == 0)
            retId = nextRid++;
        else 
        {
            retId = freedRids.back();
            freedRids.pop_back();
        }

        return retId;
    }

    void AssetManager::FreeId(uint64_t id)
    {
        if (id == nextRid - 1)
            nextRid--;
        else
            freedRids.push_back(id);
    }
}