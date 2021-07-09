#pragma once

#include <cstdint>
#include "WindowServerAPI.h"

namespace Amendieres::Windowing
{
    class ExtWindow
    {
    public:
        ExtWindow(WindowServerAPI* api);

    private:
        WindowServerAPI* server;
    };
}