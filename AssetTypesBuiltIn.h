#pragma once

#include <cstdint>
#include <limits>

namespace Amendieres
{
    /*
        The design decision here was 0 = null/empty/invalid.
        < 0 is engine-defined, stuff we're writing here.
        > 0 is game/extension-defined, stuff that might be coming from an external assembly.
        Hence why the first actual value starts at the smallest possible value, and they work up towards 0.
    */
    enum class AssetType : int32_t
    {
        Empty = -1,
        Unknown = -2,

        JsonNode = std::numeric_limits<int32_t>::min(),
    };
}