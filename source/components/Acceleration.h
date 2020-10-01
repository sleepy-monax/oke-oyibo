#pragma once

#include <debug/Inspector.h>

namespace components
{
    struct Acceleration
    {
        float ax;
        float ay;
        float az;
    };

    template <>
    void inspect<Acceleration>(entt::registry &registry, entt::entity entity)
    {
        auto &c = registry.get<Acceleration>(entity);

        ImGui::DragFloat("x##Acceleration", &c.ax, 0.1f);
        ImGui::DragFloat("y##Acceleration", &c.ay, 0.1f);
        ImGui::DragFloat("z##Acceleration", &c.az, 0.1f);
    }
} // namespace components
