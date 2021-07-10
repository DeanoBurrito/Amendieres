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

    void SfmlWindowServer::ProcessEvents()
    {
        for (auto& window : windows)
        {
            sf::RenderWindow* sfWindow = static_cast<sf::RenderWindow*>(window.second.sfObj);
            ExtWindow* localWindow = static_cast<ExtWindow*>(window.second.localObj);

            sf::Event ev;
            while (sfWindow->pollEvent(ev))
            {
                switch (ev.type)
                {
                case sf::Event::Closed:
                    break;
                case sf::Event::GainedFocus:
                    break;
                case sf::Event::LostFocus:
                    break;
                case sf::Event::Resized:
                    {
                        sf::Vector2u lastWindowSize = sfWindow->getSize();
                        localWindow->lastSize.x = static_cast<int64_t>(lastWindowSize.x);
                        localWindow->lastSize.y = static_cast<int64_t>(lastWindowSize.y);
                    }
                    break;
                
                default:
                    break;
                }
            }
        }
    }

    uint64_t SfmlWindowServer::ExtWindow_Create(ExtWindow* inst, const uint64_t width, const uint64_t height, const std::string& title, bool canResize)
    {
        sf::Uint32 windowStyle = sf::Style::Titlebar | sf::Style::Close;
        if (canResize)
            windowStyle |= sf::Style::Resize;
        
        uint64_t windowId = idManager.AllocId();
        sf::RenderWindow* sfWindow = new sf::RenderWindow(sf::VideoMode(width, height), title, windowStyle);

        inst->canResize = canResize;
        inst->lastSize = Vector2i(width, height);

        //not checking return value, as if this fails, we'll have much bigger problems.
        windows.try_emplace(windowId, Gfx::SfmlBoundObj(inst, sfWindow, Gfx::SfmlBoundObjType::Window));
        LOG("New window created.");

        return windowId;
    }

    uint64_t SfmlWindowServer::ExtWindow_Create(ExtWindow* inst, const uint64_t width, const uint64_t height, const std::string& title, bool canResize, void* appSpecific)
    {
        LOG_ERROR("SFML window server does not implement custom window settings yet. Calling this method is an error");
        return 0;
    }

    void SfmlWindowServer::ExtWindow_Destroy(uint64_t windowId)
    {
        auto windowPair = windows.find(windowId);
        if (windowPair == windows.end())
        {
            LOG_ERROR("Cannot destroy SFML window as it does not exist, or is not managed by this server.");
            return;
        }

        //get pointers and remove window from map
        sf::RenderWindow* sfWindow = static_cast<sf::RenderWindow*>(windowPair->second.sfObj);
        windows.erase(windowId);

        //TODO: notify render server of window destruction

        LOG("Window destroyed.");
        idManager.FreeId(windowId);
        sfWindow->close();
        delete sfWindow;
    }

    bool SfmlWindowServer::ExtWindow_Resize(uint64_t windowId, const uint64_t newWidth, const uint64_t newHeight)
    { 
        auto windowPair = windows.find(windowId);
        if (windowPair == windows.end())
        {
            LOG_ERROR("Cannot resize SFML window as it does not exist, or is not managed by this server.");
            return false;
        }

        ExtWindow* localWindow = static_cast<ExtWindow*>(windowPair->second.localObj);
        if (!localWindow->canResize)
        {
            LOG_ERROR("Cannot resize SFML window, resizing disabled by ctor.");
            return false;
        }

        sf::RenderWindow* sfWindow = static_cast<sf::RenderWindow*>(windowPair->second.sfObj);
        sfWindow->setSize(sf::Vector2u(newWidth, newHeight));

        sf::Vector2u actualSize = sfWindow->getSize();
        localWindow->lastSize = Vector2i(static_cast<int64_t>(actualSize.x), static_cast<int64_t>(actualSize.y));
        if (actualSize.x != newWidth || actualSize.y != newHeight)
        {
            LOG_ERROR("Window resize failed. Attempted resolution " << newWidth << "x" << newHeight << ", actaual is " << actualSize.x << "x" << actualSize.y);
            return false;
        }

        return true;
    }

    void SfmlWindowServer::ExtWindow_GoFullscreen(uint64_t windowId)
    {
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode(); //TODO: could use getFullscreenModes() and choose from the best there. This could be exposed as a setting in the server

        auto windowPair = windows.find(windowId);
        if (windowPair == windows.end())
        {
            LOG_ERROR("Cannot go fullscreen in sfml window, this window is not managed by this server.");
            return;
        }

        ExtWindow_Resize(windowId, desktopMode.width, desktopMode.height);
    }

    Vector2i SfmlWindowServer::ExtWindow_GetSize(uint64_t windowId)
    {
        auto windowPair = windows.find(windowId);
        if (windowPair == windows.end())
        {
            LOG_ERROR("Cannot get window size. It does not exist, or is not managed by this server.");
            return Vector2i();
        }

        ExtWindow* localWindow = static_cast<ExtWindow*>(windowPair->second.localObj);
        return localWindow->lastSize;
    }
}