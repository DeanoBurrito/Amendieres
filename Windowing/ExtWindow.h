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

    private:
        WindowServerAPI* server;
        bool canResize;
        Vector2i lastSize;
    };
}