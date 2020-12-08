#include "core/World.h"

#include "base/components/Move.h"
#include "base/components/Player.h"
#include "base/systems/Input.h"
#include "game/components/Attack.h"
#include "game/components/HoldItem.h"
#include "game/components/Hunger.h"
#include "game/components/Inventory.h"
#include "game/components/Menu.h"

namespace base
{
    void Input::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<Player, Position, Move, game::Menu>();

        view.each([&](entt::entity entity,
                      Player &player,
                      Position &position,
                      Move &move,
                      game::Menu &menu) {
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
                if (world.entities().has<game::Attack>(entity))
                {
                    auto &attack = world.entities().get<game::Attack>(entity);
                    attack.attacking = true;
                }
            }

            if (controller.pressed(core::Control::ACTION_SECONDARY))
            {
                if (world.entities().has<game::Hunger>(entity) &&
                    world.entities().has<game::Inventory>(entity) &&
                    world.entities().has<game::HoldItem>(entity))
                {
                    auto &hunger = world.entities().get<game::Hunger>(entity);
                    auto &inventory = world.entities().get<game::Inventory>(entity);
                    auto &hold_item = world.entities().get<game::HoldItem>(entity);

                    if (hold_item.index < inventory.inventory.count())
                    {
                        auto item = inventory.inventory[hold_item.index].item();

                        if (item.flags() & game::Item::FOOD)
                        {
                            if (item.flags() & game::Item::SUPER_FOOD)
                            {
                                hunger.current_food += 5;
                            }
                            else
                            {
                                hunger.current_food += 2;
                            }

                            if (hunger.current_food > hunger.max_food)
                            {
                                hunger.current_food = hunger.max_food;
                            }

                            inventory.remove(inventory.inventory[hold_item.index].item(), 1);
                        }
                    }
                }
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
