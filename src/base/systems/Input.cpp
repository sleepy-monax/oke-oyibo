#include "core/World.h"

#include "base/components/Acceleration.h"
#include "base/components/Player.h"
#include "base/systems/Input.h"

namespace base
{
    void Input::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<Player, Acceleration>();

        view.each([&](auto &player, auto &acceleration) {
            core::Controller &controller = world.players()[player.player_index].controller();

            if (controller.down(core::Control::MOVE_UP))
            {
                acceleration.ay -= 0.05;
            }

            if (controller.down(core::Control::MOVE_DOWN))
            {
                acceleration.ay += 0.05;
            }

            if (controller.down(core::Control::MOVE_LEFT))
            {
                acceleration.ax -= 0.05;
            }

            if (controller.down(core::Control::MOVE_RIGHT))
            {
                acceleration.ax += 0.05;
            }

            if (controller.pressed(core::Control::ZOOM_IN))
            {
                world.players()[player.player_index].camera().zoom_in();
            }

            if (controller.pressed(core::Control::ZOOM_OUT))
            {
                world.players()[player.player_index].camera().zoom_out();
            }
        });
    }
} // namespace base
