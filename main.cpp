#include <vector>
#include <string>
#include <memory>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Windowing/SfmlWindowServer.h"
#include "Json/JsonNode.h"
#include "Json/JsonParser.h"

#include "main_utils.cpp"

namespace Amendieres
{
    bool keepRunning = true;
    Windowing::SfmlWindowServer windowServer;
    Windowing::ExtWindow* mainWindow;

    sf::Clock loopClock;
    std::unique_ptr<JsonNode> mainConfig;

    int32_t updateLowerBound = 8; //default of ~120fps cap
    
    bool Init(const std::string assetsDir)
    {
        JsonParser configParser;
        mainConfig = configParser.ParseFile(assetsDir + "/config.json");
        if (mainConfig->type == JsonNodeType::Null)
           return false;
        
        JsonNumberInt* cfgWindowWidth = mainConfig->Find<JsonNumberInt>("window/width");
        JsonNumberInt* cfgWindowHeight = mainConfig->Find<JsonNumberInt>("window/height");
        sf::VideoMode windowVideoMode
            (
                cfgWindowWidth != nullptr ? cfgWindowWidth->value : 800,
                cfgWindowHeight != nullptr ? cfgWindowHeight->value : 600
            );

        RegisterAssetFactories();
        AssetManager::The()->ReadConfig(assetsDir);
        AssetManager::The()->LoadAll();

        windowServer.Init("Servers/Window.cfg");
        mainWindow = windowServer.ExtWindow_Create(800, 600, "Hello window server", true);

        return true;
    }

    void Shutdown()
    {
        windowServer.ExtWindow_Destroy(mainWindow);
        windowServer.Shutdown();
        AssetManager::The()->ClearAll();
    }

    void Update(const sf::Time delta)
    {
        windowServer.ProcessEvents();
    }

    void Render()
    {
        
    }

    void MainLoop()
    {
        loopClock.restart(); //since clock has been running since creation, at program start
        while (keepRunning)
        {
            if (loopClock.getElapsedTime().asMilliseconds() >= updateLowerBound)
            {
                sf::Time delta = loopClock.restart();
                Update(delta);
                Render();
            }
        }
    }
}

//i know, global variable. But its already global info anyway, get off my back.
std::vector<std::string> programArgs;

int main(int argc, char** argv)
{
    using namespace Amendieres;

    //processing command line args
    std::string assetsDir = "assets";
    for (int i = 0; i < argc; i++)
    {
        programArgs.push_back(argv[i]);

        std::string flagname;
        if (programArgs[i].find('='))
        {
            flagname = programArgs[i].substr(0, programArgs[i].find('='));

            if (flagname.compare("--assets") == 0)
                assetsDir = programArgs[i].substr(programArgs[i].find('=') + 1);
        }
    }

    if (!Init(assetsDir))
        return -1;
    MainLoop();
    Shutdown();

    return 0;
}