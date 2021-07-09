#pragma once

#include <stack>

namespace Amendieres
{
    template <typename backingType, std::enable_if_t<std::is_integral<backingType>::value, bool> = true> 
    class IdManager
    {
    public:
        IdManager<backingType>()
        {
            nextId = 1; //0 generally reserved for null use.
        }

        backingType AllocId()
        {
            if (freeIds.empty())
                return nextId++;
            return freeIds.pop();
        }

        void FreeId(backingType id)
        {
            if (id == nextId + 1)
                nextId--;
            else
                freeIds.push(id);
        }

    private:
        backingType nextId;
        std::stack<backingType> freeIds;
    };
}