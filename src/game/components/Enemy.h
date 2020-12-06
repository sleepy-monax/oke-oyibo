#pragma once

#include "raylib.h"

#include "editor/Inspect.h"

namespace game
{
    struct Enemy
    {
        bool isWaterCreature = false;
        bool has_focus = false;
        entt::entity target{};

        float focus_distance = 4;
        float wandering_distance = 8;
    };
} // namespace game