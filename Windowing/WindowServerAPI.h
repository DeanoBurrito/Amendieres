#pragma once

#include <string>
#include <cstdint>
#include "../Vectors.h"

namespace Amendieres::Windowing
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
        virtual void ProcessEvents() = 0;

        //External window stuff
        virtual ExtWindow* ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize) = 0;
        virtual ExtWindow* ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize, void* appSpecific) = 0;
        virtual void ExtWindow_Destroy(ExtWindow* window) = 0;
        virtual bool ExtWindow_Resize(ExtWindow* window, const uint64_t newWidth, const uint64_t newHeight) = 0;
        virtual void ExtWindow_GoFullscreen(ExtWindow* window) = 0;
        virtual Vector2i ExtWindow_GetSize(ExtWindow* window) = 0;
    };
}