#include "core/World.h"

#include "base/components/Momentum.h"
#include "base/components/Player.h"
#include "base/systems/Input.h"

namespace base
{
    void Input::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<Player, Momentum>();

        view.each([&](auto &player, auto &momentum) {
            core::Controller &controller = world.players()[player.player_index].controller();

            if (controller.down(core::Control::MOVE_UP))
            {
                momentum.ay -= 0.05;
            }

            if (controller.down(core::Control::MOVE_DOWN))
            {
                momentum.ay += 0.05;
            }

            if (controller.down(core::Control::MOVE_LEFT))
            {
                momentum.ax -= 0.05;
            }

            if (controller.down(core::Control::MOVE_RIGHT))
            {
                momentum.ax += 0.05;
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
