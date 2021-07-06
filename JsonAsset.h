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

        bool Create(std::istream& stream) override;
        void Destroy() override;
    private:
        JsonAsset(uint64_t rid);
        ~JsonAsset();
    };
}