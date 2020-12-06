#pragma once

#include "editor/Inspect.h"

namespace game
{
    struct Attack
    {
        int base_damages = 1;
        float range = 1;
        float cooldown = 0;
        bool attacking = false;
    };
} // namespace game

template <>
inline void inspect<game::Attack>(game::Attack &a)
{
    ImGui::InputInt("base_damage##Attack", &a.base_damages);
    ImGui::InputFloat("range##Attack", &a.range);
    ImGui::InputFloat("cooldown##Attack", &a.cooldown);
    ImGui::Checkbox("attacking##Attack", &a.attacking);
}