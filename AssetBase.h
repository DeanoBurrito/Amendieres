#pragma once

#include <cstdint>
#include <istream>
#include <variant>
#include "AssetTypesBuiltIn.h"

namespace Amendieres
{
    class AssetManager;
    
    class AssetBase
    {
    friend AssetManager;
    public:
        uint64_t GetId();
        AssetType GetType();
        template <class T, int c>
        std::variant<AssetType, T> GetType()
        {
            if (type >= 0)
            {
                if (type < c)
                    return std::variant<AssetType, T>(static_cast<T>(type));
                else
                    return std::variant<AssetType, T>(AssetType::Unknown);
            }
            else 
            {
                return std::variant<AssetType, T>(static_cast<AssetType>(type));
            }
        }

    protected:
        AssetBase(uint64_t rid, int32_t rType);
        virtual ~AssetBase();

        virtual bool Create(std::istream& stream) = 0;
        virtual void Destroy() = 0;
    private:
        const uint64_t id;
        const int32_t type;
    };

    class EmptyAsset : public AssetBase
    {
    friend AssetManager;
    private:
        EmptyAsset() : AssetBase(0, static_cast<int32_t>(AssetType::Empty)) {}
        bool Create(std::istream &stream) override { return true; }
        void Destroy() override {}
    };
}