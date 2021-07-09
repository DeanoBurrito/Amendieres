#pragma once

#include <unordered_map>
#include <vector>
#include "../Gfx/SfmlBoundObj.h"
#include "WindowServerAPI.h"
#include "../IdManager.h"

namespace Amendieres::Windowing
{
    class SfmlWindowServer : public WindowServerAPI
    {
    public:
        void Init(const std::string& configName) override;
        void Shutdown() override;
        bool ReloadConfig(const std::string& newConfig = nullptr) override;
        void ProcessEvents() override;

        uint64_t ExtWindow_Create(ExtWindow* inst, const uint64_t width, const uint64_t height, const std::string& title, bool canResize) override;
        uint64_t ExtWindow_Create(ExtWindow* inst, const uint64_t width, const uint64_t height, const std::string& title, bool canResize, void* appSpecific) override;
        void ExtWindow_Destroy(uint64_t windowId) override;
        bool ExtWindow_Resize(uint64_t windowId, const uint64_t newWidth, const uint64_t newHeight) override;
        void ExtWindow_GoFullscreen(uint64_t windowId) override;
        Vector2i ExtWindow_GetSize(uint64_t windowId) override;
    
    private:
        std::unordered_map<uint64_t, Gfx::SfmlBoundObj> windows;
        IdManager<uint64_t> idManager;
    };
}