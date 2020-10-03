#pragma once

#include "editor/Inspect.h"

namespace core::components
{
    struct Velocity
    {
        float vx;
        float vy;
        float vz;
    };

} // namespace core::components

template <>
void inspect<core::components::Velocity>(core::components::Velocity &vel)
{
    ImGui::DragFloat("x##Velocity", &vel.vx, 0.1f);
    ImGui::DragFloat("y##Velocity", &vel.vy, 0.1f);
    ImGui::DragFloat("z##Velocity", &vel.vz, 0.1f);
}