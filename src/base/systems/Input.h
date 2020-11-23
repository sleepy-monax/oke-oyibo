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

        void update(core::World &world, core::Time &) override
        {
            auto view = world.entities().view<Player, Acceleration>();

            view.each([&](auto &player, auto &acceleration) {
                core::input::Controller &controller = world.players()[player.player_index].controller();

                if (controller.down(core::input::Control::MOVE_UP))
                {
                    acceleration.ay -= 0.05;
                }

                if (controller.down(core::input::Control::MOVE_DOWN))
                {
                    acceleration.ay += 0.05;
                }

                if (controller.down(core::input::Control::MOVE_LEFT))
                {
                    acceleration.ax -= 0.05;
                }

                if (controller.down(core::input::Control::MOVE_RIGHT))
                {
                    acceleration.ax += 0.05;
                }

                if (controller.pressed(core::input::Control::ZOOM_IN))
                {
                    world.players()[player.player_index].camera().zoom_in();
                }

                if (controller.pressed(core::input::Control::ZOOM_OUT))
                {
                    world.players()[player.player_index].camera().zoom_out();
                }
            });
        }
    };
} // namespace base
