#pragma once

#include "raylib.h"

#include "editor/Inspect.h"

namespace game
{
    struct Enemy
    {
        bool has_focus = false;
        entt::entity target;

        float focus_distance;
        float wandering_distance;

        Enemy()
        {
            focus_distance = 4;
            wandering_distance = 8;
        }
    };
} // namespace game