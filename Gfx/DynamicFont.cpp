#include "../Debug.h"
#include "DynamicFont.h"

namespace Amendieres::Gfx
{
    DynamicFont::DynamicFont(RenderServerAPI* const api, const char* const fontData, const uint64_t dataLength)
    {
        DEBUG_RETURN_IF(api == nullptr, "Attempted to create DynamicFont with nullptr for api.");
        DEBUG_RETURN_IF(dataLength == 0, "Attempted to create DynamicFont with no data.");

        server = api;
        id = server->DynamicFont_Create(this, fontData, dataLength);
    }

    DynamicFont::DynamicFont(RenderServerAPI* const api, const char* const fontData, const uint64_t dataLength, const uint8_t fontSize)
    {
        DEBUG_RETURN_IF(api == nullptr, "Attempted to create DynamicFont with nullptr for api.");
        DEBUG_RETURN_IF(dataLength == 0, "Attempted to create DynamicFont with no data.");

        server = api;
        id = server->DynamicFont_Create(this, fontData, dataLength, fontSize);
    }

    DynamicFont::~DynamicFont()
    {
        if (server)
            server->DynamicFont_Destroy(id);
    }
}