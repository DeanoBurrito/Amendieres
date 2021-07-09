#include "../Debug.h"
#include "ExtWindow.h"

namespace Amendieres::Windowing
{
    ExtWindow::ExtWindow(WindowServerAPI* api)
    {
        if (api == nullptr)
        {
            LOG_ERROR("ExtWindow was created with empty api pointer!");
        }

        server = api;
    }
}