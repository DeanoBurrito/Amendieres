#include "../Debug.h"
#include "WindowServerAPI.h"

namespace Amendieres::Windowing
{
    static WindowServerAPI* currentInst = nullptr;

    void WindowServerAPI::SetInstance(WindowServerAPI *const inst)
    {
        LOG_ERROR_IF(currentInst != nullptr, "WindowSever instance is being overwritten by another server, this may have unintended consequences!");

        currentInst = inst;
    }


    WindowServerAPI* WindowServerAPI::The()
    {
        LOG_ERROR_IF(currentInst == nullptr, "Get() on WindowServerAPI instance is currently nullptr!");

        return currentInst;
    }
}