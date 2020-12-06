#include "core/World.h"

#include "base/components/Move.h"
#include "base/components/Player.h"
#include "base/systems/Input.h"

namespace base
{
    void Input::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<Player, Position, Move>();

        view.each([&](Player &player, Position &position, Move &move) {
            core::Controller &controller = world.players()[player.player_index].controller();

            utils::Vec2f offset;

            if (controller.down(core::Control::MOVE_UP))
            {
                offset += utils::Vec2f{0, -1};
            }

            if (controller.down(core::Control::MOVE_DOWN))
            {
                offset += utils::Vec2f{0, 1};
            }

            if (controller.down(core::Control::MOVE_LEFT))
            {
                offset += utils::Vec2f{-1, 0};
            }

            if (controller.down(core::Control::MOVE_RIGHT))
            {
                offset += utils::Vec2f{1, 0};
            }

            offset = offset.normalized();

            if (offset.length() > 0.5)
            {
                move.move_to(position() + offset * core::Tile::SIZE);
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
