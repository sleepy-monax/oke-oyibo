#pragma once

#include <raylib.h>

#include "base/components/Acceleration.h"
#include "base/components/Player.h"
#include "core/System.h"
#include "core/World.h"

namespace base
{
    class Input : public core::System
    {
    private:
    public:
        Input() : System("Input")
        {
        }

        ~Input() override
        {
        }

        void update(core::World &world, core::UpdateContext &) override
        {
            auto view = world.entities().view<Player, Acceleration>();

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
} // namespace base
