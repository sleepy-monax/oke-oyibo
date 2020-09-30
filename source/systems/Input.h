#pragma once

#include <raylib.h>

#include "components/Acceleration.h"
#include "components/Player.h"

#include "systems/System.h"
#include "world/World.h"

namespace systems
{
    class Input : public System
    {
    private:
    public:
        Input() : System("Input")
        {
        }

        ~Input() override
        {
        }

        void update(world::World &world) override
        {
            auto view = world.entities().view<components::Player, components::Acceleration>();

            view.each([](auto &player, auto &acceleration) {
                if (player.player_index == 0)
                {
                    if (IsKeyDown(KEY_UP))
                    {
                        acceleration.ay -= 1.0;
                    }
                }
            });
        }
    };
} // namespace systems
