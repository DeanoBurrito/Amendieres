#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Debug.h"
#include "ExtWindow.h"
#include "SfmlWindowServer.h"

namespace Amendieres::Windowing
{
    void SfmlWindowServer::Init(const std::string& configName)
    {
        LOG("SFML window server initializing.");
        SetInstance(this);
    }

    void SfmlWindowServer::Shutdown()
    {
        LOG("SFML window server shutting down.");
    }

    bool SfmlWindowServer::ReloadConfig(const std::string& newConfig)
    { return true; }

    ExtWindow* SfmlWindowServer::ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize)
    {
        sf::Uint32 windowStyle = sf::Style::Titlebar | sf::Style::Close;
        if (canResize)
            windowStyle |= sf::Style::Resize;
        
        ExtWindow* localWindow = new ExtWindow(this);
        sf::RenderWindow* sfWindow = new sf::RenderWindow(sf::VideoMode(width, height), title, windowStyle);

        localWindow->canResize = canResize;
        localWindow->lastSize = Vector2i(width, height);

        //not checking return value, as if this fails, we'll have much bigger problems.
        windows.try_emplace(localWindow, Gfx::SfmlBoundObj(localWindow, sfWindow, Gfx::SfmlBoundObjType::Window));
        LOG("New window created.");

        return localWindow;
    }

    ExtWindow* SfmlWindowServer::ExtWindow_Create(const uint64_t width, const uint64_t height, const std::string& title, bool canResize, void* appSpecific)
    {
        LOG_ERROR("SFML window server does not implement custom window settings yet. Calling this method is an error");
        return nullptr;
    }

    void SfmlWindowServer::ExtWindow_Destroy(ExtWindow* window)
    {
        auto windowPair = windows.find(window);
        if (windowPair == windows.end())
        {
            LOG_ERROR("Cannot destroy SFML window as it does not exist, or is not managed by this server.");
            return;
        }

        //get pointers and remove window from map
        sf::RenderWindow* sfWindow = static_cast<sf::RenderWindow*>(windowPair->second.sfObj);
        windows.erase(window);

        //TODO: notify render server of window destruction

        sfWindow->close();
        delete sfWindow;
        delete window;
    }

    bool SfmlWindowServer::ExtWindow_Resize(ExtWindow* window, const uint64_t newWidth, const uint64_t newHeight)
    { 
        return false;
    }

    void SfmlWindowServer::ExtWindow_GoFullscreen(ExtWindow* window)
    {}
}