#pragma once

#include <raylib.h>

#include "base/components/Player.h"
#include "base/components/Position.h"

#include "core/System.h"
#include "core/World.h"

#include "game/components/Health.h"
#include "game/components/Hunger.h"
#include "game/components/Thirst.h"
#include "game/components/Inventory.h"
#include "game/components/Stamina.h"

namespace game
{
    class ReviveSystem : public core::System
    {
        private:
        public:
        ReviveSystem();

        void render(core::World &world, core::Camera &camera) override;
        void reset(game::Health &health, game::Hunger &hunger, game::Thirst &thirst, game::Stamina &stamina);
    };
}