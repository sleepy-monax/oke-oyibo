#pragma once

#include <debug/Inspector.h>

namespace components
{
    struct Velocity
    {
        float vx;
        float vy;
        float vz;
    };

    template <>
    void inspect<Velocity>(entt::registry &registry, entt::entity entity)
    {
        auto &c = registry.get<Velocity>(entity);

        ImGui::DragFloat("x##Velocity", &c.vx, 0.1f);
        ImGui::DragFloat("y##Velocity", &c.vy, 0.1f);
        ImGui::DragFloat("z##Velocity", &c.vz, 0.1f);
    }
} // namespace components
