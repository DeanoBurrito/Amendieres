#pragma once

#include <cstdint>
#include <istream>

namespace Amendieres
{
    class AssetBase
    {
    public:
    protected:
        AssetBase(uint64_t rid);
        virtual ~AssetBase();

        virtual bool Create(std::istream& stream) = 0;
        virtual void Destroy() = 0;
    private:
        uint64_t id;
    };
}