#pragma once

#include <string>
#include <cstdint>

namespace Amendieres::Gfx
{
    class ExtWindow;
    
    class WindowServerAPI
    {
    public:
        static void SetInstance(WindowServerAPI* const inst);
        static WindowServerAPI* The();

        virtual void Init(const std::string& configName) = 0;
        virtual void Shutdown() = 0;
        virtual bool ReloadConfig(const std::string& newConfig = nullptr) = 0;

        //External window stuff
        virtual ExtWindow* ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize);
        virtual ExtWindow* ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize, void* appSpecific);
        virtual void ExtWindow_Destroy(ExtWindow* window);
        virtual bool ExtWindow_Resize(ExtWindow* window, const uint64_t newWidth, const uint64_t newHeight);
        virtual void ExtWindow_GoFullscreen(ExtWindow* window);
    };
}