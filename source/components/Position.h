#pragma once

#include <debug/Inspector.h>

namespace components
{
    struct Position
    {
        float x;
        float y;
        float z;
    };

    template <>
    void inspect<Position>(entt::registry &registry, entt::entity entity)
    {
        auto &c = registry.get<Position>(entity);

        ImGui::DragFloat("x##Position", &c.x, 0.1f);
        ImGui::DragFloat("y##Position", &c.y, 0.1f);
        ImGui::DragFloat("z##Position", &c.z, 0.1f);
    }
} // namespace components
