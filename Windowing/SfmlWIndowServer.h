#pragma once

#include "WindowServerAPI.h"

namespace Amendieres::Windowing
{
    class SfmlWindowServer : public WindowServerAPI
    {
        void Init(const std::string& configName) override;
        void Shutdown() override;
        bool ReloadConfig(const std::string& newConfig = nullptr) override;

        ExtWindow* ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize) override;
        ExtWindow* ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize, void* appSpecific) override;
        void ExtWindow_Destroy(ExtWindow* window) override;
        bool ExtWindow_Resize(ExtWindow* window, const uint64_t newWidth, const uint64_t newHeight) override;
        void ExtWindow_GoFullscreen(ExtWindow* window) override;
    };
}