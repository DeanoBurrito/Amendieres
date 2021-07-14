#include "../Debug.h"
#include "ExtWindow.h"

namespace Amendieres::Windowing
{   
    ExtWindow::ExtWindow(WindowServerAPI* api, const uint64_t w, const uint64_t h, const std::string& title, bool resize)
    {
        DEBUG_RETURN_IF(api == nullptr, "ExtWindow was created with api set as nullptr!");

        server = api;
        windowId = server->ExtWindow_Create(this, w, h, title, resize);
    }

    ExtWindow::~ExtWindow()
    {
        if (server != nullptr && windowId > 0) //if we're id=0 we've already been cleaned up. If the server is dead, it shouldve cleaned up any resources anyway.
            server->ExtWindow_Destroy(windowId);
    }

    void ExtWindow::Resize(uint64_t width, uint64_t height)
    {
        if (server != nullptr)
            server->ExtWindow_Resize(windowId, width, height);
    }

    Vector2i ExtWindow::GetSize()
    {
        return lastSize;
    }

    void ExtWindow::GoFullscreen()
    {
        if (server != nullptr)
            server->ExtWindow_GoFullscreen(windowId);
    }

    Gfx::RenderTexture2D* ExtWindow::GetRenderTexture()
    {
        if (server != nullptr)
            return server->ExtWindow_GetRenderTexture(windowId);
        return nullptr;
    }
}