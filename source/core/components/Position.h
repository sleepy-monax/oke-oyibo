#pragma once

#include "editor/Inspect.h"

namespace core::components
{
    struct Position
    {
        float x;
        float y;
        float z;
    };

} // namespace core::components

template <>
inline void inspect<core::components::Position>(core::components::Position &pos)
{
    ImGui::InputFloat("x##Position", &pos.x);
    ImGui::InputFloat("y##Position", &pos.y);
    ImGui::InputFloat("z##Position", &pos.z);
}
