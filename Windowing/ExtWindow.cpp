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

    void ExtWindow::Resize(uint64_t width, uint64_t height)
    {
        if (server != nullptr)
            server->ExtWindow_Resize(this, width, height);
    }

    Vector2i ExtWindow::GetSize()
    {
        return lastSize;
    }

    void ExtWindow::GoFullscreen()
    {
        if (server != nullptr)
            server->ExtWindow_GoFullscreen(this);
    }
}