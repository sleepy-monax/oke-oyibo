#pragma once

#include "editor/Inspect.h"

namespace core::components
{
    struct Acceleration
    {
        float ax;
        float ay;
        float az;
    };

} // namespace core::components

template <>
void inspect<core::components::Acceleration>(core::components::Acceleration &acc)
{
    ImGui::DragFloat("x##Acceleration", &acc.ax, 0.1f);
    ImGui::DragFloat("y##Acceleration", &acc.ay, 0.1f);
    ImGui::DragFloat("z##Acceleration", &acc.az, 0.1f);
}