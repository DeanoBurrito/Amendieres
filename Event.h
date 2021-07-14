#pragma once

#include <functional>
#include <vector>

namespace Amendieres
{
    template<typename ... Args>
    class Event
    {
    public:
        void Subscribe(void (*callback)(Args ... ))
        {
            subscribers.push_back(callback);
        }

        void Fire(Args ... args)
        {
            for (auto cb : subscribers)
            {
                cb(args ... );
            }
        }
    
    private:
        std::vector<void (*) (Args ...)> subscribers;
    };
}