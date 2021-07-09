#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "SfmlWIndowServer.h"

namespace Amendieres::Windowing
{
    void SfmlWindowServer::Init(const std::string& configName)
    {}

    void SfmlWindowServer::Shutdown()
    {}

    bool SfmlWindowServer::ReloadConfig(const std::string& newConfig)
    { return true; }

    ExtWindow* SfmlWindowServer::ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize)
    {}

    ExtWindow* SfmlWindowServer::ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize, void* appSpecific)
    {}

    void SfmlWindowServer::ExtWindow_Destroy(ExtWindow* window)
    {}

    bool SfmlWindowServer::ExtWindow_Resize(ExtWindow* window, const uint64_t newWidth, const uint64_t newHeight)
    { return true; }

    void SfmlWindowServer::ExtWindow_GoFullscreen(ExtWindow* window)
    {}
}