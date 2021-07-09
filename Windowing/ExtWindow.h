#pragma once

#include <cstdint>
#include <string>
#include "../Vectors.h"
#include "WindowServerAPI.h"

namespace Amendieres::Windowing
{
    class SfmlWindowServer;
    //class GlfwWindowServer;
    
    class ExtWindow
    {
    friend SfmlWindowServer;
    //friend GlfwWindowServer;

    public:
        ExtWindow() = delete;
        ExtWindow(const uint64_t w, const uint64_t h, const std::string& title, bool canResize) : ExtWindow(WindowServerAPI::The(), w, h, title, canResize) {}
        ExtWindow(WindowServerAPI* api, const uint64_t w, const uint64_t h, const std::string& title, bool canResize);
        ~ExtWindow();

        void Resize(uint64_t width, uint64_t height);
        Vector2i GetSize();
        void GoFullscreen();

    private:
        WindowServerAPI* server;
        uint64_t windowId;

        bool canResize;
        Vector2i lastSize;
    };
}