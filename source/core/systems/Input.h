#pragma once

#include <raylib.h>

#include "core/components/Acceleration.h"
#include "core/components/Player.h"
#include "core/systems/System.h"
#include "core/world/World.h"

namespace core::systems
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

        void update(
            world::World &world,
            game::UpdateContext &) override
        {
            auto view = world.entities().view<components::Player, components::Acceleration>();

            view.each([](auto &player, auto &acceleration) {
                if (player.player_index == 0)
                {
                    if (IsKeyDown(KEY_UP))
                    {
                        acceleration.ay -= 1.0;
                    }

                    if (IsKeyDown(KEY_DOWN))
                    {
                        acceleration.ay += 1.0;
                    }

                    if (IsKeyDown(KEY_LEFT))
                    {
                        acceleration.ax -= 1.0;
                    }

                    if (IsKeyDown(KEY_RIGHT))
                    {
                        acceleration.ax += 1.0;
                    }
                }
            });
        }
    };
} // namespace core::systems
