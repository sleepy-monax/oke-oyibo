#pragma once

#include "editor/Inspect.h"

namespace base
{
    struct Velocity
    {
        float vx;
        float vy;
        float vz;
    };

} // namespace base

template <>
inline void inspect<base::Velocity>(base::Velocity &vel)
{
    ImGui::DragFloat("x##Velocity", &vel.vx, 0.1f);
    ImGui::DragFloat("y##Velocity", &vel.vy, 0.1f);
    ImGui::DragFloat("z##Velocity", &vel.vz, 0.1f);
}