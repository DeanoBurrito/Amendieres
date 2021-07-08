#pragma once

#include "JsonParser.h"
#include "AssetBase.h"

namespace Amendieres
{
    class JsonAsset : AssetBase
    {
    public:
        static AssetBase* Factory(uint64_t id);

        std::unique_ptr<JsonNode> root;

        bool Create(char* data, uint64_t dataCount) override;
        void Destroy() override;
    private:
        JsonAsset(uint64_t rid);
        ~JsonAsset();
    };
}