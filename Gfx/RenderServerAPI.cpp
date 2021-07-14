#include "../Debug.h"
#include "RenderServerAPI.h"

namespace Amendieres::Gfx
{
    static RenderServerAPI* currentInst = nullptr;
    
    void RenderServerAPI::SetInstance(RenderServerAPI* const inst)
    {
        LOG_ERROR_IF(currentInst != nullptr, "RenderServerAPI instance is being overwritten, this is unplanned for. Do so at your own risk.");

        currentInst = inst;
    }

    RenderServerAPI* RenderServerAPI::The()
    {
        LOG_ERROR_IF(currentInst == nullptr, "Get() on RenderServerAPI instance nullptr!");

        return currentInst;
    }
}