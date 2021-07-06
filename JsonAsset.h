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

        JsonAsset(uint64_t rid);
        ~JsonAsset();

        bool Create(std::istream& stream) override;
        void Destroy() override;
    private:
    };
}