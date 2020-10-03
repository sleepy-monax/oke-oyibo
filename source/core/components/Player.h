#pragma once

#include "editor/Inspect.h"

namespace core::components
{
    struct Player
    {
        int player_index;
    };
} // namespace core::components

template <>
void inspect<core::components::Player>(core::components::Player &pla)
{
    ImGui::InputInt("player##Player", &pla.player_index);
}
