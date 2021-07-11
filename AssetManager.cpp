#include <fstream>
#include <cassert>
#include "Debug.h"
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

        LOG("Loading asset bundle from: " << directory);
        JsonArray* headerArray = configFile->Find<JsonArray>("assets");
        if (headerArray == nullptr)
        {
            LOG_ERROR("Failed to load asset config from: " << directory);
            return;
        }

        for (auto entryNode : headerArray->elements)
        {
            LoadAssetEntry(entryNode, directory);
        }
    }

    void AssetManager::LoadAll()
    {
        if (assets[0] == nullptr)
        {
            //create empty asset
            assets[0] = new EmptyAsset();
        }

        for (auto header : headers)
            Load(header.first);
    }

    void AssetManager::UnloadAll()
    {
        for (auto& header : headers)
        {
            if (header.second->loaded)
                Unload(header.first);
        }
        assert(assets.size() == 1);
    }

    void AssetManager::ClearAll()
    {
        UnloadAll();
        for (auto& asset : headers)
            delete asset.second;
        headers.clear();
    }

    void AssetManager::Load(const std::string& path)
    {
        //lookup header, abort op if it dosnt exist
        auto header = headers.find(path);
        if (header == headers.end())
        {
            LOG_ERROR("Unable to load resource with path: " << path);
            return;
        }

        if (header->second->loaded)
            return;

        //lookup creator function for specific resource type, keep it typesafe from the get go.        
        auto factory = factories.find(header->second->loaderFunction);
        if (factory == factories.end())
        {
            LOG_ERROR("Unable to load resource, no loader registered for type: " << header->second->loaderFunction);
            return;
        }

        //validate file actually exists, and offset + length arent going to trigger any weirdness
        std::ifstream inFile(header->second->fileLocation, std::ios::in | std::ios::binary);
        if (!inFile.is_open())
        {
            LOG_ERROR("Unable to load resource" << path << ", referenced file does not exist: " << header->second->fileLocation);
            //inFile.close(); //this shouldnt do anything, i've left it as a reminder for future me to verify across multiple OS's.
            return;
        }
        inFile.seekg(0, std::ios::end);

        uint64_t fileLength = inFile.tellg();
        if (fileLength < header->second->fileOffset + header->second->fileLength)
        {
            LOG_ERROR("Unable to load resource " << path << ", file does not have enough data.");
            inFile.close();
            return;
        }

        //create isolated buffer for resource to load from
        uint64_t actualSize = header->second->fileLength == 0 ? fileLength : header->second->fileLength;
        /*  Implementation hack note:
                The extra 0 at the end of the buffer should be ignored by any assets that are reading binary data, 
                as they'll be using the buffer size we pass in.
                However, to make it easy to read text files, the trailing 0 allows the entire buffer to passed
                to a std::stringstream ctor, and is read as the end of string. */
        char copyBuffer[actualSize + 1]; 
        copyBuffer[actualSize] = 0; 
        inFile.seekg(header->second->fileOffset);
        inFile.read(copyBuffer, actualSize);
        inFile.close(); 

        //create asset with unique id, cache it and create it using file from earlier
        AssetBase* base = factory->second(idManager.AllocId());
        if (!base->Create(copyBuffer, actualSize))
        {
            //std::cerr << "Unable to load resource, Create() failed. " << path << std::endl;
            LOG_ERROR("Unable to load resource, Create() failed. " << path);
            
            delete base;
            idManager.FreeId(base->id);
            return;
        }

        //finally link the header and instance, store instance ptr in vector for later access
        assets[base->id] = base;
        header->second->loaded = true;
        header->second->loadedId = base->id;

        LOG("Loaded asset: " << header->second->name << ", id=" << header->second->loadedId);
    }

    void AssetManager::Unload(const std::string& path)
    {
        //lookup header and validate it's loaded in the first place
        auto header = headers.find(path);
        if (header == headers.end())
        {
            LOG_ERROR("Unable to unload resource with path: " << path);
            return;
        }

        if (!header->second->loaded)
            return;
        
        //getting instance ptr
        if (assets.find(header->second->loadedId) == assets.end())
        {
            LOG_ERROR("Unable to unload resource " << path << ", could not find resource instance");
            header->second->loaded = false;
            header->second->loadedId = 0;
            return;
        }

        //destroy resource and clean up links
        AssetBase* base = assets.find(header->second->loadedId)->second;
        header->second->loaded = false;
        header->second->loadedId = 0;

        assets.erase(base->id);
        idManager.FreeId(base->id);
        base->Destroy();
        delete base;

        LOG("Unloaded asset: " << header->second->name);
    }

    void AssetManager::RegisterFactory(const std::string& name, std::function<AssetBase* (uint64_t)> func)
    {
        if (factories.find(name) != factories.end())
        {
            LOG_ERROR("Skipping factory " << name << ", a function is already registered to that type.");
            return;
        }

        factories[name] = func;
    }

    AssetHeader* AssetManager::GetHeader(const std::string& path) const
    { 
        if (headers.find(path) == headers.end())
            return nullptr;

        return headers.find(path)->second;
    }

    AssetBase* AssetManager::Get(const std::string& path)
    {
        //get header and check if resource is loaded or not
        auto header = headers.find(path);
        if (header == headers.end())
        {
            LOG_ERROR("Unable to Get() asset, nothing named: " << path);
            return nullptr;
        }

        if (!header->second->loaded)
            Load(path);
        
        if (!header->second->loaded)
            return nullptr; //Load() failed and will have emitted an error already.
        
        return assets[header->second->loadedId];
    }

    void AssetManager::LoadAssetEntry(JsonNode* node, const std::string& assetDir)
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
            fileName = assetDir + "/" + filenameNode->value;
            if (name.size() == 0)
                name = fileName;
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
            LOG_ERROR("Failed loading asset header entry: Header already exists for entry " << name);
            return;
        }
        
        //create entry if we have the essentials
        if (!essentialFilled)
        {
            LOG_ERROR("Failed loading asset header entry: Required details missing from config file. Possibly resource " << fileName);
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

        LOG("Loaded asset header: " << header->name << ", file=" << header->fileLocation);
    }
}