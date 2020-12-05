#pragma once

#include "raylib.h"

#include "editor/Inspect.h"

namespace game
{
    struct Health
    {
        int maximum;
        int current;
    };
} // namespace game

template <>
inline void inspect<game::Health>(game::Health &h)
{
    ImGui::DragInt("maximum##Health", &h.maximum, 1);
    ImGui::DragInt("current##Health", &h.current, 1);
}