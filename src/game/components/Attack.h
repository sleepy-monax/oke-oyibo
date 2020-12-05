#pragma once

#include "editor/Inspect.h"

namespace game
{
    struct Attack
    {
        int attack;
    };
} 

template <>
inline void inspect<game::Attack>(game::Attack &attack)
{
    ImGui::InputInt("attack##Attack", &attack.attack);
}