#include "InventorySystem.h"

#include "base/components/Position.h"
#include "game/components/Pickable.h"

namespace game
{
    void InventorySystem::update(core::World &world, core::Time &)
    {
        auto player = world.entities().view<game::Inventory, base::Position>();
        auto items = world.entities().view<game::Pickable, base::Position>();

        player.each([&](auto &inventory, auto &position) {
            auto pos_inventory = position();

            items.each([&](const auto entity, auto &pickable, auto &position) {
                auto pos_item = position();

                if (pos_item.distance_to(pos_inventory) <= core::Tile::SIZE / 4)
                {
                    pickable.stack = inventory.add(pickable.stack);
                    if (pickable.stack.quantity() == 0)
                    {
                        world.remove_entity(entity);
                    }
                }
            });
        });
    }
} // namespace game
