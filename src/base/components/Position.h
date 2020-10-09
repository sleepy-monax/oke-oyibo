#pragma once

#include "editor/Inspect.h"

namespace base
{
    struct Position
    {
        float x;
        float y;
        float z;
    };

} // namespace base

template <>
inline void inspect<base::Position>(base::Position &pos)
{
    ImGui::InputFloat("x##Position", &pos.x);
    ImGui::InputFloat("y##Position", &pos.y);
    ImGui::InputFloat("z##Position", &pos.z);
}
