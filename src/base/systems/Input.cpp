#include "core/World.h"

#include "base/components/Move.h"
#include "base/components/Player.h"
#include "base/systems/Input.h"
#include "game/components/Attack.h"
#include "game/components/Menu.h"

namespace base
{
    void Input::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<Player, Position, Move, game::Attack, game::Menu>();

        view.each([&](Player &player, Position &position, Move &move, game::Attack &attack, game::Menu &menu) {
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

            if (offset.length() > 0.25)
            {
                move.move_to(position() + offset * core::Tile::SIZE);
            }
            else
            {
                move.stop();
            }

            if (controller.down(core::Control::ACTION_MAIN))
            {
                attack.attacking = true;
            }

            if (controller.pressed(core::Control::MENU_OPEN))
            {
                menu.visible = !menu.visible;
            }

            if (controller.pressed(core::Control::MENU_NEXT))
            {
                menu.selected += 1;
            }

            if (controller.pressed(core::Control::MENU_PREV))
            {
                menu.selected -= 1;
            }

            if (controller.pressed(core::Control::MENU_ACTION))
            {
                menu.clicked = true;
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
