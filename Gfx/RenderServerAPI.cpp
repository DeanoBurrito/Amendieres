#include "../Debug.h"
#include "RenderServerAPI.h"

namespace Amendieres::Gfx
{
    static RenderServerAPI* currentInst = nullptr;
    
    void RenderServerAPI::SetInstance(RenderServerAPI* const inst)
    {
        if (currentInst != nullptr)
        {
            LOG_ERROR("RenderServerAPI instance is being overwritten, this is unplanned for. Do so at your own risk.");
        }
        currentInst = inst;
    }

    RenderServerAPI* RenderServerAPI::The()
    {
        if (currentInst == nullptr)
        {
            LOG_ERROR("Get() on RenderServerAPI instance nullptr!");
        }
        return currentInst;
    }
}