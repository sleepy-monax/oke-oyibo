#pragma once

#include "editor/Inspect.h"

namespace base
{
    struct Player
    {
        int player_index;
    };
} // namespace base

template <>
inline void inspect<base::Player>(base::Player &pla)
{
    ImGui::InputInt("player##Player", &pla.player_index);
}
