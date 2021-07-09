#pragma once

#include <cstdint>
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
        ExtWindow(WindowServerAPI* api);

        void Resize(uint64_t width, uint64_t height);
        Vector2i GetSize();
        void GoFullscreen();

    private:
        WindowServerAPI* server;
        bool canResize;
        Vector2i lastSize;
    };
}