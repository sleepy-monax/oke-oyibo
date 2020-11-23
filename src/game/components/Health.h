#pragma once

#include "raylib.h"

#include "editor/Inspect.h"

namespace game
{
    struct Health
    {
        int health;
    };
} // namespace game

template <>
inline void inspect<game::Health>(game::Health &h)
{
    ImGui::DragInt("health##Health", &h.health, 100);
}