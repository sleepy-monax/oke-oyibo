#include "InventorySystem.h"

#include "game/components/Pickable.h"
#include "base/components/Position.h"

namespace game
{
    InventorySystem::InventorySystem(){
    }
    InventorySystem::~InventorySystem(){}

    void InventorySystem::update(core::World &world, core::Time &) {
        auto player = world.entities().view<game::Inventory, base::Position>();
        auto items = world.entities().view<game::Pickable,base::Position>();

        player.each([&](auto &inventory, auto &position) {
           auto pos_inventory = position.pos2d();

            items.each([&](auto &pickable, auto &position) {
                auto pos_item = position.pos2d();

                if (pos_item.distance_to(pos_inventory) <= 2.)
                {
                    inventory.add(pickable.stack);
                }
                 
            });
        });
        
    }
} // namespace game
