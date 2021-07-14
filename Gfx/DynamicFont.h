#pragma once

#include "RenderServerAPI.h"
#include <string>

namespace Amendieres::Gfx
{
    class DynamicFont
    {
    public:
        DynamicFont(const std::string& assetName) 
            : DynamicFont(RenderServerAPI::The(), assetName) {}
        DynamicFont(RenderServerAPI* const api, const std::string& assetName);
        DynamicFont(const std::string& assetName, const uint8_t fontSize)
            : DynamicFont(RenderServerAPI::The(), assetName, fontSize) {}
        DynamicFont(RenderServerAPI* const api, const std::string& assetName, const uint8_t fontSize);

    private:
        RenderServerAPI* server;
    };
}