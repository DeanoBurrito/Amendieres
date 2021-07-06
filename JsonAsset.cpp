#include "JsonAsset.h"

namespace Amendieres
{
    AssetBase* JsonAsset::Factory(uint64_t id)
    {
        return nullptr;
    }
    
    JsonAsset::JsonAsset(uint64_t rid) : AssetBase(rid, static_cast<int32_t>(AssetType::JsonNode))
    {

    }

    JsonAsset::~JsonAsset()
    {}

    bool JsonAsset::Create(std::istream& stream)
    {   
        JsonParser parser;
        root = parser.ParseStream(stream);
        return true;
    }

    void JsonAsset::Destroy()
    {
        root.reset();
    }
}