#include "../Debug.h"
#include "WindowServerAPI.h"

namespace Amendieres::Windowing
{
    static WindowServerAPI* currentInst = nullptr;

    void WindowServerAPI::SetInstance(WindowServerAPI *const inst)
    {
        if (currentInst != nullptr)
        {
            LOG_ERROR("WindowSever instance is being overwritten by another server, this may have unintended consequences!");
        }
        currentInst = inst;
    }


    WindowServerAPI* WindowServerAPI::The()
    {
        if (currentInst == nullptr)
        {
            LOG_ERROR("Get() on WindowServerAPI instance is currently nullptr!");
        }
        return currentInst;
    }
}