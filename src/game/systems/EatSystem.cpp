#include "EatSystem.h"

#include "base/components/Player.h"
#include "base/components/Position.h"

#include "game/components/HoldItem.h"
#include "game/components/Hunger.h"
#include "game/components/Inventory.h"

namespace game
{
    void EatSystem::update(core::World &world, core::Time &)
    {
        auto player = world.entities().view<base::Player, game::Hunger, game::Inventory, game::HoldItem>();

        player.each([&](auto &, auto &hunger, auto &inv, auto &hold) {
            if (IsKeyPressed(KEY_C))
            {
                if (hold.index < inv.inventory.count()) {
                    string holdItem = inv.inventory[hold.index].getItem().getName();
                    if (holdItem.compare("food") == 0) {
                        if (hunger.current_food + 2 <= hunger.max_food)
                        {
                            hunger.current_food += 2;
                        }
                        else
                        {
                            hunger.current_food = hunger.max_food;
                        }
                        inv.remove(inv.inventory[hold.index].getItem(), 1);
                    }
                }
            }
        });
    }
}