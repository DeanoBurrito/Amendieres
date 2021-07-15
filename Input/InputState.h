#pragma once

#include <unordered_map>
#include <string>
#include "InputEnums.h"
#include "../Vectors.h"

namespace Amendieres::Input
{
    class InputState
    {
    public:
        bool KeyDown(const std::string& name);
        bool KeyDown(const Keys key);
        bool KeyPressed(const std::string& name);
        bool KeyPressed(const Keys key);
        bool KeyReleased(const std::string& name);
        bool KeyReleased(const Keys key);

        Vector2i GetMousePos();
        Vector2i GetMouseRelativePos();
        Vector2f GetJoystickAxis(int axisNum);
    
    private:
        std::unordered_map<std::string, Keys>* keyMappings;
        bool currentKeyStates[static_cast<int>(Keys::Count)];
        bool previousKeyStates[static_cast<int>(Keys::Count)];
    };
}