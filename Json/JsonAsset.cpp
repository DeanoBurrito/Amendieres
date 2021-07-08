#include <sstream>
#include "JsonAsset.h"

namespace Amendieres
{
    AssetBase* JsonAsset::Factory(uint64_t id)
    {
        return new JsonAsset(id);
    }
    
    JsonAsset::JsonAsset(uint64_t rid) : AssetBase(rid, static_cast<int32_t>(AssetType::JsonNode))
    {

    }

    JsonAsset::~JsonAsset()
    {}

    bool JsonAsset::Create(char* data, uint64_t dataCount)
    {   
        JsonParser parser;
        std::stringstream str(data);
        root = parser.ParseStream(str);
        return root->type != JsonNodeType::Null;
    }

    void JsonAsset::Destroy()
    {
        root.reset();
    }
}