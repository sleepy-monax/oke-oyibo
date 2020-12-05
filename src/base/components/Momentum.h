#pragma once

#include "editor/Inspect.h"

namespace base
{
    struct Momentum
    {
        float ax;
        float ay;
        float az;

        float vx;
        float vy;
        float vz;
    };
} // namespace base

template <>
inline void inspect<base::Momentum>(base::Momentum &m)
{
    ImGui::DragFloat("ax##AffectedByPhysic", &m.ax, 0.1f);
    ImGui::DragFloat("ay##AffectedByPhysic", &m.ay, 0.1f);
    ImGui::DragFloat("az##AffectedByPhysic", &m.az, 0.1f);

    ImGui::DragFloat("vx##AffectedByPhysic", &m.vx, 0.1f);
    ImGui::DragFloat("vy##AffectedByPhysic", &m.vy, 0.1f);
    ImGui::DragFloat("vz##AffectedByPhysic", &m.vz, 0.1f);
}
