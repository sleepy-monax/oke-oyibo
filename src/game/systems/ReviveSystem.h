#pragma once

#include "core/System.h"

#include "game/components/Health.h"
#include "game/components/Hunger.h"
#include "game/components/Inventory.h"
#include "game/components/Stamina.h"
#include "game/components/Thirst.h"

namespace game
{
    class ReviveSystem: public core::System
    {
        void render(core::World &world, core::Camera &camera) override;

        void reset(game::Health &health, game::Hunger &hunger, game::Thirst &thirst, game::Stamina &stamina);

        void kill_enemy(core::World &world);
    };
} // namespace game