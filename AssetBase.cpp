#include "AssetBase.h"

namespace Amendieres
{
    AssetBase::AssetBase(uint64_t rid, int32_t rType) : id(rid), type(rType)
    { }

    AssetBase::~AssetBase()
    { }

    uint64_t AssetBase::GetId()
    {
        return id;
    }

    AssetType AssetBase::GetType()
    {
        if (type >= 0)
            return AssetType::Unknown;
        return static_cast<AssetType>(type);
    }
}