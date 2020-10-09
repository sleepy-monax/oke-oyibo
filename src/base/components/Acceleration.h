#pragma once

#include "editor/Inspect.h"

namespace base
{
    struct Acceleration
    {
        float ax;
        float ay;
        float az;
    };

} // namespace base

template <>
inline void inspect<base::Acceleration>(base::Acceleration &acc)
{
    ImGui::DragFloat("x##Acceleration", &acc.ax, 0.1f);
    ImGui::DragFloat("y##Acceleration", &acc.ay, 0.1f);
    ImGui::DragFloat("z##Acceleration", &acc.az, 0.1f);
}